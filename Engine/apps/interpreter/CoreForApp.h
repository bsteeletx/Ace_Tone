#ifndef _H_COREFORAPP
#define _H_COREFORAPP

// interpreter header
#include "interpreter.h"

#ifdef IDE_MEEGO
// need access to main app ptr
extern QApplication* g_appptr;
#endif

// interpreter init code
int AppInitCode ( void )
{
	// SETUP FILE can override certain initial properties of an executable
	// such as the width and height
	App.g_dwDeviceWidth = DEVICE_WIDTH;
	App.g_dwDeviceHeight = DEVICE_HEIGHT;
	App.g_dwFullScreen = 0;
	App.g_dwResolutionMode = 0;
	#ifdef IDE_BADA
	// Bada does not need SETUP.AGC (mobile app package wirh fixed resolution) (and no support for ATOI)
	#else
	char* pSetupFile = (char*)"setup.agc";
	if ( agk::GetFileExists ( pSetupFile )==1 )
	{
		char* pField = (char*)"";
		strcpy ( App.g_pWindowTitle, "" );
		agk::OpenToRead ( 1, pSetupFile );
		while ( agk::FileEOF ( 1 )==false )
		{
			char* pLineToRead = agk::ReadLine ( 1 );
			pField=(char*)"title="; if ( strncmp ( pLineToRead, pField, strlen(pField) )==0 )	strcpy ( App.g_pWindowTitle, pLineToRead+strlen(pField) );
			pField=(char*)"width="; if ( strncmp ( pLineToRead, pField, strlen(pField) )==0 )	App.g_dwDeviceWidth = (unsigned int)atoi(pLineToRead+strlen(pField));
			pField=(char*)"height="; if ( strncmp ( pLineToRead, pField, strlen(pField) )==0 )	App.g_dwDeviceHeight = (unsigned int)atoi(pLineToRead+strlen(pField));
			pField=(char*)"fullscreen="; if ( strncmp ( pLineToRead, pField, strlen(pField) )==0 )	App.g_dwFullScreen = (unsigned int)atoi(pLineToRead+strlen(pField));
			pField=(char*)"resolutionmode="; if ( strncmp ( pLineToRead, pField, strlen(pField) )==0 )	App.g_dwResolutionMode = (unsigned int)atoi(pLineToRead+strlen(pField));
		}
		agk::CloseFile ( 1 );

		// WINDOWS
		#ifdef AGKWINDOWS
		if ( App.g_dwDeviceWidth==0 ) App.g_dwDeviceWidth = GetSystemMetrics ( SM_CXSCREEN );
		if ( App.g_dwDeviceHeight==0 ) App.g_dwDeviceHeight = GetSystemMetrics ( SM_CYSCREEN );
		#endif
	}
	#endif

	// WINDOWS
	#ifdef AGKWINDOWS
	// If app already running, quit
	HANDLE g_hWindowMutex = CreateMutex ( NULL, TRUE, App.g_pWindowTitle );
	if ( g_hWindowMutex!=NULL )
	{
		if ( GetLastError()== ERROR_ALREADY_EXISTS )
		{
			CloseHandle ( (HANDLE)g_hWindowMutex );
			return 0;
		}
	}
	// If app is free version, must have compiler in predictable location (identified by registry)
	#ifdef FREEVERSION
     char pAGLInstallationPath [ 512 ];
     strcpy ( pAGLInstallationPath, "" );
     HKEY keyCode = 0;
     LONG ls = RegOpenKeyEx( HKEY_CURRENT_USER, _T("Software\\The Game Creators\\App Game Kit"), NULL, KEY_QUERY_VALUE, &keyCode );
     if ( ls == ERROR_SUCCESS )
     {
        DWORD dwType=REG_SZ;
        DWORD dwSize=512;
        ls = RegQueryValueEx ( keyCode, _T("INSTALL"), NULL, &dwType, (LPBYTE)pAGLInstallationPath, &dwSize );
     }
     if ( keyCode!=0 ) RegCloseKey( keyCode );
	 strcat ( pAGLInstallationPath, "IDE\\Compiler\\AGKCompiler.exe" );
	 HANDLE hfile = CreateFile ( pAGLInstallationPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	 if ( hfile != INVALID_HANDLE_VALUE )
	 {
		// compiler exists, allow executable to run
		CloseHandle ( hfile );
	 }
	 else
	 {
		// compiler file does not exist, must be trying to run the EXE on another PC
		MessageBox ( NULL, "This executable must be run on the same machine as the AGK Trial Version", "AGK Trial Message", MB_OK );
		return 0;
	 }
	#endif
	#endif
	#ifdef IDE_MAC
	// a way to keep only ONE mac app running at any one time
	#endif

	// success
	return 1;
}

void RuntimError ( const char* pErrorString )
{
	// remembers the command responsible for this error (including line number)
	App.RememberLastCommand();
	
	// also prompt runtime error here for good measure
	if ( App.IsRunning() )
	{
		// work out if line in main program or an include
		LPSTR pIncludeFile = "";
		DWORD dwFinalLine = App.GetLastLineNumber();
		if ( App.g_dwIncludesMax > 1 )
		{
			DWORD dwI = 1;
			while ( dwFinalLine > App.g_dwIncludesPos[dwI] ) dwI++;
			dwI--; dwFinalLine = dwFinalLine - App.g_dwIncludesPos[dwI];
			pIncludeFile = App.g_pIncludesFile[dwI];
		}

		// present runtime error as messagebox
		char pFullErrorText [ 512 ];
		if ( pIncludeFile && strcmp ( pIncludeFile, "" )==NULL )
			sprintf ( pFullErrorText, "%s at line %d", pErrorString, App.GetLastLineNumber() );
		else
			sprintf ( pFullErrorText, "%s at line %d in %s", pErrorString, dwFinalLine, pIncludeFile );
		agk::Message ( pFullErrorText );
		
		// post a quit flag (standalone will exit, player will return to standby)
		App.QuitApp();
	}
}

// app can gather data about the window app
void AppGatherData ( DWORD dwhWnd, char* lpCmdLine )
{
	App.g_WindowHandle = dwhWnd;
	if ( lpCmdLine )
		strcpy ( App.g_pCmdLine, lpCmdLine );
	else
		strcpy ( App.g_pCmdLine, "" );
	
	// set-up error callback (so can handle line number detection)
	agk::SetErrorCallback ( RuntimError );	
}

// interpreter soft and hard quit functions
void AppQuitNow ( void )
{
	// close app session and set stage to quit session
	App.CloseApp();
	App.g_iAppControlStage = 91;
	
	// restores interpreter to initial aspect
	App.UpdateInterpreterAspect();
}

void AppForceExit ( void )
{
	// 310811 - free version
	#ifdef FREEVERSION
	agk::SetClearColor ( 0, 0, 0 );
	agk::SetViewOffset ( 0, 0 );
	agk::StopTextInput();
	agk::SetPhysicsDebugOff();

	if ( !App.g_pAGKBackdrop.pImage ) App.g_pAGKBackdrop.pImage = new cImage ( "/interpreter-backdrop.png" );
	if ( !App.g_pAGKBackdrop.pSprite ) App.g_pAGKBackdrop.pSprite = new cSprite ( App.g_pAGKBackdrop.pImage );
	App.g_pAGKBackdrop.pSprite->FixToScreen ( 1 );
	if ( !App.g_pAGKBackdropSpinner.pImage ) App.g_pAGKBackdropSpinner.pImage = new cImage ( "/interpreter-spinner.png" );
	if ( !App.g_pAGKBackdropSpinner.pSprite ) App.g_pAGKBackdropSpinner.pSprite = new cSprite ( App.g_pAGKBackdropSpinner.pImage );
	App.g_pAGKBackdropSpinner.pSprite->SetAlpha ( 16 );
	App.g_pAGKBackdropSpinner.pSprite->FixToScreen ( 1 );
	if ( !App.g_pAGKBackdropLogo.pImage ) App.g_pAGKBackdropLogo.pImage = new cImage ( "/interpreter-logo.png" );
	if ( !App.g_pAGKBackdropLogo.pSprite ) App.g_pAGKBackdropLogo.pSprite = new cSprite ( App.g_pAGKBackdropLogo.pImage );
	App.g_pAGKBackdropLogo.pSprite->FixToScreen ( 1 );

	App.UpdateInterpreterAspect();
	// agk::MasterReset();
	DWORD dwTimerEnd = timeGetTime() + 3000;
	AGK::cText* pSlashText[3];
	cImage* pArial = new cImage( "/Arial.png" );

	
	for ( int t=0; t<3; t++ )
	{
		pSlashText[t] = new AGK::cText ();
		pSlashText[t]->SetAlignment ( 1 );
		pSlashText[t]->SetFontImage( pArial );
		pSlashText[t]->FixToScreen ( 1 );
		pSlashText[t]->SetPosition ( 50, 10+(t*75.0f) );
		pSlashText[t]->SetColor ( 32, 32, 32, 255 );
		pSlashText[t]->SetSize ( 6.0f-(t*2.5f) );
		if ( t==0 ) pSlashText[t]->SetString (  "TRIAL APPLICATION" );
		if ( t==1 ) pSlashText[t]->SetString (  "this application was created in AGK\navailable from www.appgamekit.com" );
		if ( t==2 ) pSlashText[t]->SetString (  "3" );
	}

	
	int iCycleCounter = 0;
	int iFadeIn = 0;
	char szTimeLeft[32];
	while ( timeGetTime() < dwTimerEnd )
	{
		int timeleft = (dwTimerEnd - timeGetTime()) / 1000;
		sprintf( szTimeLeft, "%d", timeleft+1 );
		agk::ClearScreen();
		if ( App.g_pAGKBackdrop.pSprite ) App.g_pAGKBackdrop.pSprite->Draw();
		if ( App.g_pAGKBackdropSpinner.pSprite )
		{
			App.g_pAGKBackdropSpinner.pSprite->SetAngle ( (float)(iCycleCounter % 360) );
			App.g_pAGKBackdropSpinner.pSprite->Draw();
			iCycleCounter+=2;
		}
		if ( App.g_pAGKBackdropLogo.pSprite )
		{
			App.g_pAGKBackdropLogo.pSprite->SetAlpha ( iFadeIn );
			App.g_pAGKBackdropLogo.pSprite->Draw();
		}
		pSlashText[0]->SetAlpha((int)(iFadeIn*0.75f));
		pSlashText[0]->Draw();
		pSlashText[1]->SetAlpha((int)(iFadeIn*0.75f));
		pSlashText[1]->Draw();
		pSlashText[2]->SetPosition ( 50, 20 );
		pSlashText[2]->SetSize ( 5 );
		pSlashText[2]->SetString( szTimeLeft );
		pSlashText[2]->SetAlpha((int)(iFadeIn*0.75f));
		pSlashText[2]->Draw();
		iFadeIn+=8;
		if ( iFadeIn>255 ) iFadeIn = 255;
		agk::Swap();
	}
	delete pSlashText[0];
	delete pSlashText[1];
	delete pSlashText[2];
	#endif

	// completely exit the player/app
	#ifdef AGKWINDOWS
	PostQuitMessage(0);
	#endif
	#ifdef AGKIOS
	// forcing a quit in iOS is against recommended guidelines - use HOME button
	// the exit button is disabled on AGKIOS builds
	#endif
        #ifdef IDE_MEEGO
        g_appptr->quit();
        #endif
	#ifdef IDE_MAC
	glfwCloseWindow();
	#endif
	#ifdef IDE_BADA
	// Bada platform has a HOME button to quit apps
	// 105 - 081011 - but the END command can also quit a Bada App forcefully
	Application::GetInstance()->Terminate();
	#endif
}

#endif // _H_COREFORAPP

