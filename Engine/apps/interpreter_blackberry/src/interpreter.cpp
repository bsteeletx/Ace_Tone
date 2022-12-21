// Includes, namespace and prototypes

#include "interpreter.h"
using namespace AGK;
app App;

//#define STANDALONE

// Scrapper System
bool					g_bScrapperActive = false;
DWORD					g_dwScrapperTimeOut = 0;
#ifdef SCRAPPER
// Globals for scrapper reviewer
AGK::BroadcastListener  g_Listener;                     // listener for IP address
AGK::AGKSocket          g_Socket;                       // our socket for network communications
Texture2D*              g_pTexture      = nil;          // texture from UIImage
cSpriteEx*              g_pSprite       = NULL;         // custom sprite - had problems with being able to correctly pass the data over to AGK
char*                   g_pData         = NULL;         // buffer to store jpeg data
int                     g_iDataSize     = 100000;       // default size of jpeg data is 100k
bool                    g_bDisconnected = false;        // whether we have disconnected
int                     g_iState        = 0;            // state of app
#else
#ifdef SCRAPPERSENDER
// Globals for scrapper sender
AGK::cNetworkListener	g_NetworkListener;			// listener for connections
AGKSocket*				g_pSocket;					// socket for sending data
AGK::Broadcaster		g_Broadcaster;				// broadcaster class
AGK::AGKPacket			g_Packet;					// packet with server IP
unsigned char*			g_pData = NULL;				// image buffer
DWORD					g_dwBroadcastStreamPing = 0;
#endif
#endif

// Globals for interpreter
cNetwork g_Network1;
BroadcastListener broadcastListener;
bool g_bStartedReceiving = false;
cFileReceiver receiver;
Broadcaster g_DeviceBroadcaster;
cNetworkListener g_CompilerListener;

// Globals for remote debugger
cNetwork g_DebugNetwork;				// main network to HOST debug app (debug tool is joiner)
int* g_iDebugVarGlobalStrings = NULL;	// store whether global/local var is a string or not (reported in via debug tool)
int g_iDebugVarGlobalStringsMax = 0;
int* g_iDebugVarLocalStrings = NULL;
int g_iDebugVarLocalStringsMax = 0;

int iCycleCounter = 0;
char* g_pVersionNumber = 0;
AGK::cText* g_pInterpreterText = NULL;
extern unsigned int g_dwDeviceWidth;
extern unsigned int g_dwDeviceHeight;
extern unsigned int g_dwFullScreen;
extern unsigned int g_dwResolutionMode;
float g_fInitialAspect = 0.0f;
float g_fLastMouseX = 0.0f;
float g_fLastMouseY = 0.0f;
bool g_bResetApp = false;
bool g_bAGKViewerMode = false;
int g_iAGKViewerOrigWidth = -1;
int g_iAGKViewerOrigHeight = -1;
char g_pOriginalRootDir[512];

// called when interpreters aspect changes (keep graphics 1:1) 
void app::UpdateInterpreterAspect ( void )
{
	if ( g_fInitialAspect==0.0f ) g_fInitialAspect = agk::GetDisplayAspect();
	float fAspect = g_fInitialAspect;
	agk::SetVirtualResolution ( 100, 100 );
	agk::SetDisplayAspect(fAspect);
	if ( g_pAGKBackdrop.pSprite )
	{
		if ( fAspect >= 1.0f )
		{
			// landscape or square
			g_pAGKBackdrop.pSprite->SetSize ( 100, 100*fAspect );
			g_pAGKBackdrop.pSprite->SetPosition ( 0, (100-(100*fAspect))/2.0f );
			g_pAGKBackdropSpinner.pSprite->SetSize ( 70/fAspect, 70 );
			g_pAGKBackdropSpinner.pSprite->SetPosition ( 50-((70/fAspect)/2.0f), 25-10 );
			g_pAGKBackdropLogo.pSprite->SetSize ( 50/fAspect, 50 );
			g_pAGKBackdropLogo.pSprite->SetPosition ( 50-((50/fAspect)/2.0f), 50-(50/2.0f) );
		}
		else
		{
			// portrait
			g_pAGKBackdrop.pSprite->SetSize ( 100/fAspect, 100 );
			g_pAGKBackdrop.pSprite->SetPosition ( (100-(100/fAspect))/2.0f, 0 );
			g_pAGKBackdropSpinner.pSprite->SetSize ( 70, 70*fAspect );
			g_pAGKBackdropSpinner.pSprite->SetPosition ( 25-10, 50-((70*fAspect)/2.0f) );
			g_pAGKBackdropLogo.pSprite->SetSize ( 50, 50*fAspect );
			g_pAGKBackdropLogo.pSprite->SetPosition ( 50-(50/2.0f), 50-((50*fAspect)/2.0f) );
		}
		g_pAGKBackdropPower.pSprite->SetSize ( 10/fAspect, 10 );
		g_pAGKBackdropPower.pSprite->SetPosition ( 99-(10/fAspect), 1 );
	}
}

void app::InitClean ( void )
{
    // Delete internal files (so can be downloaded a fresh - if exist)
    // (prevents an old ASCII.PNG file sitting around for a new program to mistakenly use)
	// (for example if decide to remove joystickouter.png from project media, default is used)
    agk::DeleteFile( "/ascii.png" );
    agk::DeleteFile( "/JoystickOuter.png" );
    agk::DeleteFile( "/JoystickInner.png" );
    agk::DeleteFile( "/Button.png" );
    agk::DeleteFile( "/Arial.png" );
    agk::DeleteFile( "/Avenir.png" );
    agk::DeleteFile( "/Missing.png" );
    agk::DeleteFile( "/interpreter-backdrop.png" );
    agk::DeleteFile( "/interpreter-power.png" );
    agk::DeleteFile( "/interpreter-logo.png" );
    agk::DeleteFile( "/interpreter-spinner.png" );
}

// Begin app, called once at the start
void app::Begin( void )
{
    // 110512 - build 1073 - Windows sets the MEDIA folder on winmain (T1 default)
    // but IOS, MAC and other platforms have no internal MEDIA folder, which then
    // creates a functional difference when you code SetCurrentDir("") : SetCurrentDir("media")
    // so the T1 interpreter will Create and Enter a Media folder if one does not exist
    // T1 BASIC uses a fixed MEDIA folder
    //#ifndef AGKWINDOWS
	agk::SetCurrentDir ( "" );
	agk::MakeFolder ( "media" );
	agk::SetCurrentDir ( "media" );
    //#endif

	//agk::SetSyncRate( 60, 0 );
    
	// default resolution
	agk::SetDisplayAspect( (float)g_dwDeviceWidth/(float)g_dwDeviceHeight );

	// string to store filename to byte code
	strcpy ( g_pInterpreterByteCodeFile, "" );
	
	// non-Windows standalone apps switch to the resource folder as the current directory
	char pInterpreterByteCodeFolder[ MAX_PATH ];	
	strcpy ( pInterpreterByteCodeFolder, "" );
	
	// WINDOWS
	#ifdef AGKWINDOWS

	// Find name of this executable
	char pThisExecutable[512];
	GetModuleFileName(NULL, pThisExecutable, _MAX_PATH); // PAUL, string = agk::GetAppName() instead of getmodulefilename
	pThisExecutable [ strlen(pThisExecutable)-4 ] = 0;
	
	// Project name is app title
	char pAppName[_MAX_PATH];
	strcpy ( pAppName, pThisExecutable );
	DWORD n = strlen(pAppName);
	for (;n>0; n-- )
		if ( pAppName[n]=='\\' || pAppName[n]=='/' )
			break;
	strcpy ( pAppName, pAppName + n + 1 );
	
	// Name of byte code file when running standalone
	strcpy ( g_pInterpreterByteCodeFile, pAppName );
	strcat ( g_pInterpreterByteCodeFile, ".byc" );

	#endif
	
	// IOS
	#ifdef AGKIOS
	
	// Assign byte code filename when running standalone
    #ifdef STANDALONE
     // If building a standalone app from the latest AGK Player interpreter.cpp
     // can use STANDALONE flag in standalone project to quickly enable bytecode launching
    strcpy ( g_pInterpreterByteCodeFile, "bytecode.byc" ); // comment in for T1 BASIC APP
    #endif

	#endif
	
	// MAC
	#ifdef IDE_MAC

	NSBundle *g_pBundle = [NSBundle mainBundle];
	char szRoot[ MAX_PATH ];
	char szRootDir[ MAX_PATH ];
	char szAppFolderName[ MAX_PATH ];
	char pAppName[MAX_PATH];
	strcpy(szRoot,"");
	strcpy(szRootDir,"");
	strcpy(szAppFolderName,"");
	strcpy(pAppName,"");
	uint32_t size = MAX_PATH;
	if ( _NSGetExecutablePath(szRoot, &size) == 0 )
	{
		realpath( szRoot, szRootDir );
		uString sModule( szRootDir );
		strcpy( szAppFolderName, sModule.GetStr() );
		strcpy ( pAppName, szAppFolderName );
		DWORD n = strlen(pAppName);
		for (;n>0; n-- )
			if ( pAppName[n]=='\\' || pAppName[n]=='/' )
				break;
		strcpy ( pAppName, pAppName + n + 1 );
	}
	NSString *path = [g_pBundle resourcePath];
	strcpy ( pInterpreterByteCodeFolder, [path UTF8String] );
	strcat ( pInterpreterByteCodeFolder, "/media/" );	
#ifdef STANDALONE
    // If building a standalone app from the latest AGK Player interpreter.cpp
    // can use STANDALONE flag in standalone project to quickly enable bytecode launching
    strcpy ( g_pInterpreterByteCodeFile, "bytecode.byc" );
#else
	strcpy ( g_pInterpreterByteCodeFile, pAppName );
	strcat ( g_pInterpreterByteCodeFile, ".byc" );
#endif    
	uString sFullPathToFile( pInterpreterByteCodeFolder );
	sFullPathToFile.Append( g_pInterpreterByteCodeFile );
	cFileEntry::ConvertToReal( sFullPathToFile );
	FILE *pFile = fopen( sFullPathToFile, "rb" );
	if ( pFile )
	{
		// we merely wanted to know if the BYC file was there
		// so we can keep the interpreter byte code filename
		// when OpenToRead tries to find the BYC file it will
		// find it using the internal 'resource checker' part
		// of the AGK engine ;) Same goes for media!
		fclose ( pFile );
	}
	else
		strcpy ( g_pInterpreterByteCodeFile, "" );
	
	#endif

	// BADA
	#ifdef IDE_BADA

	// Assign byte code filename when running standalone
	// All T1 BASIC applications store media and byte code in /RES folder
    // strcpy ( g_pInterpreterByteCodeFile, "bytecode.byc" ); // comment in for T1 BASIC APP

	#endif
	
    // MEEGO
    #ifdef IDE_MEEGO

    // Assign byte code filename when running standalone
    // strcpy ( g_pInterpreterByteCodeFile, "bytecode.byc" ); // comment in for T1 BASIC APP

    // In MeeGo we are not using the resource.qrc (:/) we are
    // actually packing the files into the application files area for MeeGo
    // which is /var/opt/com.thegamecreators.com/ (MeeGo compliance)
    // and the engine provides the first part in RootDir (/var/opt/)
    // but the actual application needs to provide the rest
    // (must be identical to the .PRO application identity used)
    //agk::SetCurrentDir ( "com.yourcompany.yourapp/" );

    #endif

	#ifdef IDE_ANDROID
	
	// Assign byte code filename when running standalone
     strcpy ( g_pInterpreterByteCodeFile, "bytecode.byc" ); // comment in for T1 BASIC APP

	#endif

	#ifdef IDE_BLACKBERRY
	
	// Assign byte code filename when running standalone
     strcpy ( g_pInterpreterByteCodeFile, "bytecode.byc" ); // comment in for T1 BASIC APP

	#endif

	 if ( agk::GetFileExists(g_pInterpreterByteCodeFile) == 0 ) strcpy ( g_pInterpreterByteCodeFile, "" );

    // Once we have the byte code file, determine if we should run standalone
	// or switch to wait/standby mode as an AGK Player
	g_iAppControlStage = 0;
	g_iAppIsStandalone = 0;

	// WINDOWS
	#ifdef AGKWINDOWS

	// Default on Windows is direct run
	if ( strnicmp ( g_pCmdLine, "-wait", 5 )==NULL )
	{
		// "compiler" calls interpreter with -wait command line
		strcpy ( g_pInterpreterByteCodeFile, "" ); // wipe out BYC filename if AGK Player
		g_iAppControlStage = 1;
	}
	else
	{
		// 090911 - trigger scraper transmission
		#ifdef SCRAPPERSENDER
		if ( strnicmp ( g_pCmdLine, "-scrapper", 8 )==NULL )
		{
			// create a network host to send out streams from app running here on Windows
			g_Packet.AddInt ( 999 );
			g_Broadcaster.SetData ( 45635, &g_Packet, 10 );
			g_Broadcaster.Start ( );
			g_NetworkListener.AcceptConnections ( 45635 );
			g_dwBroadcastStreamPing = timeGetTime() + 1000;
			g_Network1.HostNetwork( "App Viewer Network", "server", 5690 );
			g_bScrapperActive = true;
			g_dwScrapperTimeOut = timeGetTime();
		}
		#endif

		// load app immediately
		g_iAppIsStandalone = 1;
		GetCurrentDirectory ( 512, g_pOriginalRootDir );
		if ( LoadApp()==true )
		{
			// this app will end as soon as it quits
		}
		else
		{
			// load failed - instant prompt
			if ( strncmp ( agk::GetLastError(), "Version Error : ", 16 )!=NULL )
				agk::Message ( agk::GetLastError() );
		}
	}

	#else

	// for non-Windows execution, if BYC file exists in this primary apps
	// resources area, then the intent is a direct execution of a Tier 1 app
	if ( strcmp ( g_pInterpreterByteCodeFile, "" ) != 0 )
	{
		// load app immediately
		g_iAppIsStandalone = 1;
		if ( LoadApp()==true )
		{
			// this app will end as soon as it quits
		}
		else
		{
			// load failed - instant prompt crude - switch back to player if BYC not exist
			// agk::Message ( agk::GetLastError() );
			agk::Error("");
			g_iAppControlStage = 1;
			g_iAppIsStandalone = 0;
		}		
	}
	else 
	{
		// Default is waiting stage (AGK Player)
		g_iAppControlStage = 1;
	}

	#endif

    // load required fonts
    if ( !g_pArialImage ) g_pArialImage = new cImage( "/Avenir.png" );
	if ( !g_pAsciiImage ) g_pAsciiImage = new cImage( "ascii.png" );

	// 100612 - build 1077 - we don't need 'AGK Player' activity when 
	// running standalone (i.e. when we have a BYC file specified)
	if ( strcmp ( g_pInterpreterByteCodeFile, "" )==NULL )
	{
		// Prepare interpreter graphics (for wait mode)
		g_pAGKBackdrop.pImage = new cImage ( "/interpreter-backdrop.png" );
		g_pAGKBackdrop.pSprite = new cSprite ( g_pAGKBackdrop.pImage );
		g_pAGKBackdrop.pSprite = new cSprite ( g_pAGKBackdrop.pImage );
        g_pAGKBackdrop.pSprite->FixToScreen ( 1 );
		g_pAGKBackdropSpinner.pImage = new cImage ( "/interpreter-spinner.png" );
		g_pAGKBackdropSpinner.pSprite = new cSprite ( g_pAGKBackdropSpinner.pImage );
		g_pAGKBackdropSpinner.pSprite->SetAlpha ( 16 );
		g_pAGKBackdropSpinner.pSprite->FixToScreen ( 1 );
		g_pAGKBackdropLogo.pImage = new cImage ( "/interpreter-logo.png" );
		g_pAGKBackdropLogo.pSprite = new cSprite ( g_pAGKBackdropLogo.pImage );
		g_pAGKBackdropLogo.pSprite->FixToScreen ( 1 );
		g_pAGKBackdropPower.pImage = new cImage ( "/interpreter-power.png" );
		g_pAGKBackdropPower.pSprite = new cSprite ( g_pAGKBackdropPower.pImage );
		g_pAGKBackdropPower.pSprite->FixToScreen ( 1 );
		for ( DWORD n=0; n<4; n++ )
		{
			g_pText[n] = new AGK::cText ();
			g_pText[n]->SetAlignment ( 1 );
			g_pText[n]->SetFontImage( g_pArialImage );
			g_pText[n]->FixToScreen ( 1 );
		}
		g_pText[0]->SetPosition ( 50, 80.0f );
		g_pText[0]->SetColor ( 0,0,0,192 );
		g_pText[1]->SetSize ( 7.0f );
		g_pText[1]->SetPosition ( 50, 86.0f );
		g_pText[1]->SetSize ( 2.5f );
		g_pText[1]->SetColor ( 0,0,0,192 );
		g_pText[2]->SetPosition ( 50, 89.0f );
		g_pText[2]->SetSize ( 2.5f );
		g_pText[2]->SetColor ( 0,0,0,192 );
		g_pText[3]->SetPosition ( 50, 97.0f );
		g_pText[3]->SetSize ( 2.0f );
		g_pText[3]->SetColor ( 0,0,0,128 );
	}

	// Ensure interpreter aspect updated
    UpdateInterpreterAspect();

	// 070911 - in FREE version, use special trial byte code
	DWORD dwAgkCommandsVersion = AGKCOMMANDSVERSION;
	#ifdef FREEVERSION
	dwAgkCommandsVersion += 10000000;
	#endif

	// create version string from version number
	g_pVersionNumber = new char[32];
	sprintf ( g_pVersionNumber, "%d", (int)dwAgkCommandsVersion );
}

// Main loop, called every frame
bool app::LoadApp ( void )
{
	// Load byte code file (pure data)
	DWORD dwActualBytesOfByteCode = 0;
	DWORD dwByteOffsetToStringTable = 0;
	char* pBYCFile = g_pInterpreterByteCodeFile;
    UINT iFileID = agk::OpenToRead ( pBYCFile );
    if( iFileID==0 )
    {
		// cannot find or open byte code file
		agk::Error( "Application file does not exist" );
        return false;
    }
	else
	{
		// read byte code into pre-created array
		g_dwByteCodeVersion = agk::ReadInteger ( iFileID );
		// 070911 - in FREE version, use special trial byte code
		DWORD dwAgkCommandsVersion = AGKCOMMANDSVERSION;
		#ifdef FREEVERSION
		dwAgkCommandsVersion += 10000000;
		#endif
        
        /* disable during 107 build work
		if ( g_dwByteCodeVersion != dwAgkCommandsVersion )
		{
			// the byte code file from the compiler and this interpreter build differ!
			agk::CloseFile( iFileID );

			// error clues
			if ( g_dwByteCodeVersion == AGKCOMMANDSVERSION ) agk::Error( "Version Error : The player and application are incompatible" );
			if ( g_dwByteCodeVersion > AGKCOMMANDSVERSION ) agk::Error( "Version Error : Update the player to continue" );
			if ( g_dwByteCodeVersion < AGKCOMMANDSVERSION ) agk::Error( "Version Error : Update the compiler to continue" );

			// fail execution
			return false;
		}
        */

		// read rest of file
		g_dwByteCodeMax = agk::ReadInteger ( iFileID );
		g_dwVariableBufferSize = agk::ReadInteger ( iFileID );
		g_dwLiteralStringMax = agk::ReadInteger ( iFileID );
		dwByteOffsetToStringTable = agk::ReadInteger ( iFileID );
		dwActualBytesOfByteCode = agk::ReadInteger ( iFileID );
		DWORD dwCR2 = agk::ReadInteger ( iFileID );
		dwCR2=dwCR2;

		// 191011 - turns out size was in bytes, but created that many sByteCode structuyres (oops)
		// g_ByteCode = new sByteCode [ (dwActualBytesOfByteCode/4) + 4 ];
		DWORD dwSizeInByteCodeBlocks = (dwActualBytesOfByteCode / sizeof(sByteCode)) + 1;
		g_ByteCode = new sByteCode [ dwSizeInByteCodeBlocks ];

		// 181011 - some devices cannot create LARGE chunks of memory to store the AGK app byte code!
		if ( g_ByteCode==NULL )
		{
			agk::CloseFile( iFileID );
			agk::Error( "Memory Error : Device ran out of memory" );
			return false;
		}

		DWORD* pByteCodePtr = (DWORD*)g_ByteCode;
		for ( DWORD dwB=0; dwB<dwActualBytesOfByteCode/4; dwB++ ) pByteCodePtr[dwB] = agk::ReadInteger ( iFileID );
		dwCR2 = agk::ReadInteger ( iFileID );
		// include strings to end (so runtime can work out which line/include file is)
		g_dwIncludesMax = agk::ReadInteger ( iFileID );
		g_dwIncludesPos = new DWORD[g_dwIncludesMax];
		g_pIncludesFile = new LPSTR[g_dwIncludesMax];
		for ( DWORD dwI=0; dwI<g_dwIncludesMax; dwI++ )
		{
			g_dwIncludesPos[dwI] = agk::ReadInteger ( iFileID );
			DWORD dwStrLength = agk::ReadInteger ( iFileID );
			DWORD* pStrPtr = (DWORD*)new char [ dwStrLength+1 ];
			for ( DWORD dwB=0; dwB<dwStrLength/4; dwB++ ) pStrPtr[dwB] = agk::ReadInteger ( iFileID );
			g_pIncludesFile[dwI] = (char*)pStrPtr;
		}
		dwCR2 = agk::ReadInteger ( iFileID );
		agk::CloseFile( iFileID );
    }

	// Reset Interpreter (run from first instruction)
	DWORD dwSizeOfOneInstructionSlot = sizeof(sByteCode);
	g_pByteCodePtr = &g_ByteCode[0];
	g_pByteCodeEnd = g_pByteCodePtr + dwActualBytesOfByteCode;
	//g_iInstructionCounterStart = dwActualBytesOfByteCode / dwSizeOfOneInstructionSlot;
	g_iInstructionCounterStart = 20000; // 071111 - above does not account for LARGE loops at start of app
	g_dwByteCodeLastLineNumber = 0;

	// Create variable buffer
	g_pVarBuffer = new char[g_dwVariableBufferSize];
	memset ( g_pVarBuffer, 0, g_dwVariableBufferSize );

	// Copy literal string table from byte code data
	char* pDataPtr = ((char*)g_pByteCodePtr )+ dwByteOffsetToStringTable;
	g_pLiteralString = new char* [g_dwLiteralStringMax+1];
	for ( DWORD dwI=0; dwI<g_dwLiteralStringMax; dwI++ )
	{
		DWORD dwStringLength = *(DWORD*)pDataPtr;
		pDataPtr+=4;
		char* pString = new char[1+dwStringLength];
		memset ( pString, 0, 1+dwStringLength );
		memcpy ( pString, pDataPtr, dwStringLength );
		pDataPtr+=dwStringLength;
		g_pLiteralString[dwI] = pString;
	}

	// Create subroutine stack
	g_dwSubroutineStackMax = 100;
	g_pSubroutineStack = new sByteCode* [ g_dwSubroutineStackMax ];
	g_pSubroutineStackEBPStore = new char* [ g_dwSubroutineStackMax ];
	g_dwSubroutineStackIndex = 0;

	// Create user function stack
	g_dwStackMax = 10240;
	g_pStack = new char [ g_dwStackMax ];
	memset ( g_pStack, 0, g_dwStackMax ); // 171011 - clear function stack (as users expect local vars to be zero!!)
	g_pStackPtr = g_pStack;
	g_pStackPtrEBP = g_pStack;
	g_pStackEnd = g_pStack + g_dwStackMax;
	g_pStackPtrStartOfLocalVarMemBlock = NULL;

	// Flashback system
	g_dwFBI = 0;
	memset ( g_pFB, 0, sizeof(sByteCode*)*FBMAX );

	// Set-up remote debugging system
	g_bRemoteDebuggingActive = false;
	g_bRemoteDebuggingInProgress = false;
	g_iRemoteDebuggingLastLineRemembered = -1;
	g_iRemoteDebuggingMode = 0;
	g_iRemoteDebuggingAdvanceToLine = 0;

	// Reset timer
	g_fScreenFPS = 0.0f;
	g_iFrameCount = 0;
	g_lLastTimer = 0;
	g_lTimer = 0;

    // reset any states from main engine (from any previous run)
    agk::ResetAllStates();

    // Set default font for app
	AGK::cText::SetDefaultFontImage( g_pAsciiImage );

	// load succeeded
	return true;
}

// temp
LONGLONG lLastTime = 0;
UINT g_iNetworkCurrentlyActive = 0;
UINT g_iCountUp = 0;

float posx = 50;
float posy = 50;
char g_szCompilerIP[ 40 ];
UINT g_iCompilerPort = 0;
UINT g_iFilePort = 0;
uString g_sGameName;

// Main loop, called every frame
void app::WaitingLoop ( void )
{
	// loop when we are listening out for apps
	if ( g_iAppControlStage==1 || g_iAppControlStage==2 || g_iAppControlStage==3 )
	{
		#ifdef SCRAPPER
		// scrapper is ONLY interested in joining a pre-existing HOST network (already running on Windows)
		g_iAppControlStage = 2;
		#else
		// watch for device connection to compiler before we launch the app
		if ( g_iAppControlStage == 1 )
		{
			// hyjack this stage as a device broadcast to get compiler IP before connecting to the network.
			if ( !g_DeviceBroadcaster.IsRunning() ) 
			{
				AGKPacket packet;
				packet.AddUInt( 5687 );
				g_DeviceBroadcaster.SetData( 5688, &packet, 1000 );
				g_DeviceBroadcaster.Start();
			}

			if ( !g_CompilerListener.IsRunning() ) 
			{
				g_CompilerListener.AcceptConnections( 5687 );
			}

			AGKSocket *pReply = g_CompilerListener.GetNewConnection();
			if ( pReply )
			{
				g_DeviceBroadcaster.Stop();
				g_CompilerListener.Stop();

				strcpy( g_szCompilerIP, pReply->GetRemoteIP() );
				g_iCompilerPort = pReply->RecvUInt();
				g_iFilePort = pReply->RecvUInt();
				pReply->RecvString( g_sGameName );
				if ( g_iCompilerPort > 0 )
				{
					g_iAppControlStage = 2;
				}

				delete pReply;
			}
		}
		#endif
	
		if ( g_iAppControlStage==2 || g_iAppControlStage==3 )
		{
			// if no network, join a host
			if ( g_Network1.IsActive()==false )
			{
				// cleanup if a previous network in place
				if ( g_iNetworkCurrentlyActive==1 )
				{
					#ifdef IDE_BADA
					// Samsung Bada has problems if you shut down network over and over!
					#else
					g_Network1.CloseNetwork();
					g_Network1.Reset();
					#endif
				}

				// join the compiler
				LPSTR pInterpreterNetworkName = (LPSTR)"interpreter";
				#ifdef AGKWINDOWS
				pInterpreterNetworkName = "interpreterWIN";
				#endif
				#ifdef AGKIOS
				pInterpreterNetworkName = (LPSTR)"interpreterIOS";
				#endif
				#ifdef IDE_MAC
				pInterpreterNetworkName = (LPSTR)"interpreterMAC";
				#endif
				#ifdef IDE_MEEGO
				pInterpreterNetworkName = "interpreterMEEGO";
				#endif
				#ifdef IDE_BADA
				pInterpreterNetworkName = "interpreterBADA";
				#endif
				#ifdef SCRAPPER
				g_Network1.JoinNetwork( "App Viewer Network", pInterpreterNetworkName );
				#else
				//g_Network1.JoinNetwork( "App Control Network", pInterpreterNetworkName );
				// interpreters now direct connect to the network
				g_Network1.JoinNetwork( g_szCompilerIP, g_iCompilerPort, pInterpreterNetworkName );
				#endif
			}
			else
			{
				// as soon as there are two on the network, we have an active network (connected)
				if ( g_Network1.GetNumClients()>1 && g_iNetworkCurrentlyActive == 0 )
				{
					// connection to host successful
					g_iNetworkCurrentlyActive = 1;
				}
			}

			// wait for compiler to send us messages / files
			cNetworkMessage *pMsg = g_Network1.GetMessage();
			while ( pMsg )
			{
				uString sSenderName;
				UINT clientID = pMsg->GetSenderID();
				// Paul: can use  clientID == g_Network1.GetServerID() to check for server
				g_Network1.GetClientName( clientID, sSenderName );
				uString sMessageText;
				pMsg->GetString( sMessageText );

				// cross platform method of depositing warnings
				agk::Warning( sMessageText.GetStr() );

				if ( strcmp ( sSenderName.GetStr(), "server" )==0 )
				{
					// message from server(compiler)
					if ( strcmp ( sMessageText.GetStr(), "i have stream" )==0 )
					{
						#ifdef SCRAPPER
						// scrapper does not accept files/code - it simply renders video stream
						App.g_iAppControlStage = 1001;
						#else
						// byte code mode handled below
						#endif
					}
					// message from server(compiler)
					if ( strcmp ( sMessageText.GetStr(), "i have app" )==0 )
					{
						#ifdef SCRAPPER
						// stream mode handled above
						#else
						// compiler has an app, say we want it (so compiler can increase the app count and keep sending until all interpreters have their apps)
						cNetworkMessage *pResponseMsg = new cNetworkMessage();
						pResponseMsg->AddString("i want app");
						g_Network1.SendMessage ( pMsg->GetSenderID(), pResponseMsg );
						
						// if we are not in 'receive mode' do that now
						if ( g_iAppControlStage!=3 )
						{
							// only now do we start listening for files (bind broadcast listener)
							//broadcastListener.SetListenPort( 45632 );
							
							// and go file receiving stage
							g_iAppControlStage = 3;
							g_iCountUp = 0;
						}
						#endif
					}
				}
				delete pMsg;
				pMsg = g_Network1.GetMessage();
			}
		}

		// AGK HUD
		#ifdef SCRAPPER
		 LPSTR pAGKHUDPrompt0 = (LPSTR)"WAITING FOR STREAM";
		 LPSTR pAGKHUDPrompt1 = (LPSTR)"Device ready to receive video stream";
		 LPSTR pAGKHUDPrompt2 = (LPSTR)"and return all device input data";
		#else
		 LPSTR pAGKHUDPrompt0 = (LPSTR)"STANDBY";
		 LPSTR pAGKHUDPrompt1 = (LPSTR)"To exit a running app, simply press the";
		 LPSTR pAGKHUDPrompt2 = (LPSTR)"top of the screen for 5 seconds";
		#endif
		if ( g_iAppControlStage > 0 )
		{
			if ( g_pAGKBackdrop.pSprite ) g_pAGKBackdrop.pSprite->Draw();
			if ( g_pAGKBackdropSpinner.pSprite )
			{
				g_pAGKBackdropSpinner.pSprite->SetAngle ( (float)(iCycleCounter % 360) );
				g_pAGKBackdropSpinner.pSprite->Draw();
				iCycleCounter++;
			}
			if ( g_pAGKBackdropLogo.pSprite ) g_pAGKBackdropLogo.pSprite->Draw();
			
			// some platforms need to power off button
			#ifdef AGKIOS
			 // no power off button on all iOS platforms - against guidelines - they use HOME button
			#else
			#ifdef IDE_BADA
			 // no power off button on Bada platform
			#else
			 // draw power off button
			 if ( g_pAGKBackdropPower.pSprite ) g_pAGKBackdropPower.pSprite->Draw();
			 // when rendering front view, can quit from it
			 if ( agk::GetPointerPressed()==1 )
			 {
				 float fAspect = agk::GetDisplayAspect();
				 float fShutOffWidth = agk::GetVirtualWidth()/10.0f;
				 if ( agk::GetPointerX() > agk::GetVirtualWidth()-fShutOffWidth && agk::GetPointerY() < agk::GetVirtualHeight()/10.0f )
				 {
					// switch to QUIT and STANDALONE to exit player
					g_iAppControlStage=91;
					g_iAppIsStandalone=1;
				 }
			 }
			#endif
			#endif
		}

		// check for broadcasts from compiler
		if ( g_iAppControlStage==3 )
		{
			// server is broadcasting files now
			/*
			if ( broadcastListener.ReceivedBroadcast() )
			{
				// see packet
				AGKPacket packet;
				UINT fromPort;
				char fromIP[ 40 ];
				broadcastListener.GetPacket( packet, fromPort, fromIP );
				uString sGameName;
				packet.GetString( sGameName );
				UINT returnPort = packet.GetUInt();

				// receiver is not currently connected and working
				if ( receiver.IsFinished() )
				{
                    // game name passes in BYC filename (and app name.byc)
					strcpy ( g_pInterpreterByteCodeFile, sGameName.GetStr() );

                    // use app name to create a sub folder in current write temp area
                    char pNoExtension[MAX_PATH];
                    strcpy(pNoExtension, sGameName.GetStr());
                    pNoExtension[strlen(pNoExtension)-4]=0;
                    agk::SetAppName ( pNoExtension );

					// delete old BYC file before download new one
					agk::DeleteFile ( g_pInterpreterByteCodeFile );

					// connect to server and start receiving files..
					if ( receiver.ConnectTo( fromIP, returnPort, 3000 ) )
					{
						g_bStartedReceiving = true;
						receiver.Start();
					}
					else
					{
						 //NSLog( @"Failed to connect to file sender to get files" );
					}
				}
			}
			*/

			// connect directly to the file broadcaster
			if ( receiver.IsFinished() && !g_bStartedReceiving )
			{
                // game name passes in BYC filename (and app name.byc)
				strcpy ( g_pInterpreterByteCodeFile, g_sGameName.GetStr() );

                // use app name to create a sub folder in current write temp area
                char pNoExtension[MAX_PATH];
                strcpy(pNoExtension, g_sGameName.GetStr());
                pNoExtension[strlen(pNoExtension)-4]=0;
                agk::SetAppName ( pNoExtension );

				// delete old BYC file before download new one
				agk::DeleteFile ( g_pInterpreterByteCodeFile );

				// connect to server and start receiving files..
				if ( receiver.ConnectTo( g_szCompilerIP, g_iFilePort, 3000 ) )
				{
					g_bStartedReceiving = true;
					receiver.Start();
				}
			}

			g_iCountUp++; // I want a time value!
			if ( g_bStartedReceiving==false && g_iCountUp > 500 )
			{
				// i wanted app but did not get a broadcast of files
				broadcastListener.Close();
				#ifdef IDE_BADA
				// Samsung Bada has problems if you shut down network over and over!
				#else
				g_Network1.CloseNetwork();
				g_Network1.Reset();
				#endif
				g_iNetworkCurrentlyActive = 0;
				g_iAppControlStage = 1;
			}
		}
		if ( g_bStartedReceiving==true )
		{
			// once files fully received..
			if ( receiver.IsFinished() )
			{
				// reset it so we can use it again if necessary
				g_bStartedReceiving = false;
				receiver.Reset();
				if ( receiver.IsSuccess() )
				{
					// when we have all the files, launch app
					g_iAppControlStage = 11;
				}
				else
				{
					// failed to receive files
					g_iAppControlStage = 1;
				}

				// stop listening for files
				broadcastListener.Close();

				// clean up joiner issues by closing network to allow a fresh join (host can die, restart, die, restart)
				#ifdef IDE_BADA
				// Samsung Bada has problems if you shut down network over and over!
				#else
				g_Network1.CloseNetwork();
				g_Network1.Reset();
				#endif
				g_iNetworkCurrentlyActive = 0;
			}
			else
			{
				// download progress
				pAGKHUDPrompt0 = (LPSTR)"RECEIVING APP";
				if ( receiver.GetProgress() > 0 )
				{
					char pProgressText[128];
                    sprintf ( pProgressText, "%d%%", (int)receiver.GetProgress() );
					pAGKHUDPrompt1 = pProgressText;
				}
				else
					pAGKHUDPrompt1 = (LPSTR)"";
				pAGKHUDPrompt2 = (LPSTR)"";
			}
		}
		else
		{
			// waiting
			/* cool feature to show last 9 line numbers - trace back
			agk::Print( "" );
			agk::Print( "Flashback Report:" );
			DWORD dwTraceInstruction = GetFlashbackPos();
			for ( DWORD n=0; n<FBMAX; n++ )
			{
				if ( dwTraceInstruction>0 )
					dwTraceInstruction--;
				else
					dwTraceInstruction=FBMAX-1;
				sByteCode* pFlashbackInstPtr = GetFlashbackInstruction(dwTraceInstruction);
				agk::PrintC( 1+n );
				agk::PrintC( ". " );
				if ( pFlashbackInstPtr )
				{
					agk::PrintC( "Line " );
					agk::Print( pFlashbackInstPtr->dwLineNumber );
				}
				else
					agk::Print( "?" );
			}
			*/
			// runtime error info
            // fixed memory leak by calling GetLastError() without deleting the returned string
            uString sErr;
            agk::GetLastError(sErr);
			if ( sErr.GetLength() > 1 )
			{
				pAGKHUDPrompt0 = (LPSTR)"LAST ERROR";
                char pLine[1024]; //Paul: 512 not long enough
                strcpy ( pLine, sErr.GetStr() );
				if ( GetLastLineNumber()>0 )
				{
                    sprintf ( pLine, "%s at line %d", pLine, GetLastLineNumber() );
				}
                if ( strlen ( pLine )>35 )
                {
                    // cut up error message
                    char pLineTwo[512];
                    DWORD n = 0;
                    for ( n=35; n>0; n-- )
                        if ( pLine[n]==' ' )
                            break;

                    strcpy ( pLineTwo, pLine + n );
                    pLine [ n ]=0;
                    pAGKHUDPrompt1 = pLine;
                    pAGKHUDPrompt2 = pLineTwo;
                }
                else
                {
                    // fits on one line
                    pAGKHUDPrompt1 = pLine;
                    pAGKHUDPrompt2 = (LPSTR)"";
                }
			}
			// network info
            int iClientCount = g_Network1.GetNumClients();
            if ( g_Network1.IsActive() && iClientCount>0 )
			{
				#ifdef SCRAPPER
				 pAGKHUDPrompt0 = (LPSTR)"STREAM IS ACTIVE";
				#else
				 pAGKHUDPrompt0 = (LPSTR)"NETWORK IS ACTIVE";
				#endif
				pAGKHUDPrompt1 = (LPSTR)"";
				pAGKHUDPrompt2 = (LPSTR)"";
			}
		}

		// draw text to AGK HUD
		if ( g_pText[0] )
		{
			g_pText[0]->SetString ( pAGKHUDPrompt0 );
			g_pText[0]->Draw();
			g_pText[1]->SetString ( pAGKHUDPrompt1 );
			g_pText[1]->Draw();
			g_pText[2]->SetString ( pAGKHUDPrompt2 );
			g_pText[2]->Draw();
			#ifdef SCRAPPER
			 g_pText[3]->SetString ( "you must broadcast app from AGK IDE" );
			 g_pText[3]->Draw();
			#else
			 if ( g_pVersionNumber )
			 {
				uString version(g_pVersionNumber);
				version.Append( " build " );
				version.Append( __DATE__ );
				g_pText[3]->SetString ( version );
				g_pText[3]->Draw();
			 }
			#endif
		}
	}

	// always conduct a client clean-up system
	if ( g_Network1.IsActive())
	{
		int clientID = g_Network1.GetFirstClient();
		while ( clientID > 0 )
		{
			if ( g_Network1.GetClientDisconnected(clientID)==1 ) g_Network1.DeleteDisconnectedClient(clientID);
			clientID = g_Network1.GetNextClient();
		}
	}

	// when ready, we LAUNCH the app
	if ( g_iAppControlStage==11 )
	{
		// end network client link
		#ifdef IDE_BADA
		// Samsung Bada has problems if you shut down network over and over!
		#else
		g_Network1.CloseNetwork();
		g_Network1.Reset();
		#endif
		
		// clear any old errors
		agk::Error("");
		App.ClearLastCommand();

		// clear screen to ensure no player artefacts in render
		agk::Sync();
		agk::Sync();

		// load app from local media
		if ( LoadApp()==true )
		{
			// trigger main loop
			g_iAppControlStage = 0;
		}
		else
		{
			// load failed - instantly back to wait screen
			g_iAppControlStage = 91;
		}
	}

	// when quit an app (END), close last app and return to waiting
	if ( g_iAppControlStage==91 )
	{
		// standalone exits immediately
		CloseApp();
		
		if ( g_iAppIsStandalone==0 )
		{
			// back to wait page
			g_iAppControlStage = 1;

			// set app folder back to the interpreter (to stay away from app folder contents)
			agk::RestoreWriteDir();
			
			// restores interpreter to initial aspect
			App.UpdateInterpreterAspect();
		}
		else
		{
			// now force a quit (platform specific)
			AppForceExit();
		}
	}

	// agk must keep humming along
	agk::Sync();
}

// Scrapper will handle video stream IN and input data OUT
void app::ScrapperLoop ( void )
{
	// video stream - this function renders the incoming stream to the view
	#ifdef SCRAPPER
	if ( App.g_iAppControlStage==1001 )
	{
		// init stream process
		#ifdef SCRAPPER

		// default of iPad max resolution - squashed down for iPod and iPhone by AGK
		agk::SetVirtualResolution ( 1024, 768 );
		g_Listener.SetListenPort ( 45635 );
		g_pSprite  = new cSpriteEx ( );
		g_pData    = new char [ g_iDataSize ];
		g_pTexture = [ Texture2D alloc ];			
		App.g_iAppControlStage = 1002;
		#endif
	}
	if ( App.g_iAppControlStage==1002 )
	{
		// hook up with server
		if ( g_iState == 0 )
		{
			// check for a broadcast
			if ( g_Listener.ReceivedBroadcast ( ) )
			{
				// get the packet
				AGK::AGKPacket packet;
				unsigned int port;
				char szIP [ 256 ] = "";
				
				g_Listener.GetPacket ( packet, port, &szIP [ 0 ] );
				
				// connect to the IP address being sent out
				g_Socket.Connect ( szIP, 45635 );
				
				// switch to next state
				g_bDisconnected = false;
				g_iState = 1;
			}
			
			// ensure device with accelerometer is able to use it
			// so we freeze the orientation in stream mode once AGK Player oriented by player (in standby phase)
			agk::SetOrientationAllowed ( 0,0,0,0 );			
			
			// send message to Windows screen scrapper sender that it should present to be an iOS device
			int iRawDataType = 101;
			cNetworkMessage *pRawDataReturnMessage = new cNetworkMessage();
			pRawDataReturnMessage->AddInt( iRawDataType );
			pRawDataReturnMessage->AddInt( agk::GetDeviceWidth() );
			pRawDataReturnMessage->AddInt( agk::GetDeviceHeight() );
			g_Network1.SendMessage( 0, pRawDataReturnMessage );
			
			// return when we're waiting
			return;
		}
        
		// if disconnected, reset stream until next one?
		if ( g_bDisconnected==true )
		{
			// reset for AGK engine
			[ g_pTexture dealloc ];
			g_pTexture = [ Texture2D alloc ];
			delete g_pSprite;
			g_pSprite  = new cSpriteEx ( );
			g_Network1.CloseNetwork();
			g_Network1.Reset();		
			agk::MasterReset();
			g_iState = 0;
			// clear any warnings
			agk::Warning("");
			// return control to wait stage
			g_iAppControlStage = 91;
			return;
		}
		
		// first chunk of data we receive tells us how big the incoming image is
		int iImageSize = g_Socket.RecvInt ( );
		
		// check our connection
		if ( g_Socket.GetDisconnected ( ) == true )
		{
			g_Socket.Close();
			g_Listener.Close();
			g_Listener.SetListenPort ( 45635 );
			g_bDisconnected = true;
			return;
		}
		
		// next step is to deal with the incoming image
		if ( iImageSize > 0 )
		{
			// if this image is larger than our buffer then we'll increase the size
			if ( iImageSize > g_iDataSize )
			{
				// bump up the size to 150%
				g_iDataSize = iImageSize * 1.5;
				
				// wipe out our previous array
				delete [ ] g_pData;
				
				// finally build a new array
				g_pData = new char [ g_iDataSize ];
			}
			
			// we now need to loop round until all the data from the image arrives
			int iOffset   = 0;
			int iSize     = iImageSize;
			int iReceived = 0;

			// adjust size of virtual resolution based on size requested by app
			int iImageWidth = g_Socket.RecvInt ( );
			int iImageHeight = g_Socket.RecvInt ( );			
			agk::SetVirtualResolution ( iImageWidth, iImageHeight );
			
			// keep going until we have all the data
			while ( iOffset != iImageSize )
			{
				// get a block of data, may not necessarily be all the data
				iReceived = g_Socket.RecvData ( &g_pData [ iOffset ], iSize );
				
				// check our connection
				if ( g_Socket.GetDisconnected ( ) == true )
				{
					g_Socket.Close();
					g_Listener.Close();
					g_Listener.SetListenPort ( 45635 );
					g_bDisconnected = true;
					return;
				}
				
				// deduct the size and increase the offset
				iSize   -= iReceived;
				iOffset += iReceived;
			}
			
			// create a blank image with the jpeg data
			CGDataProviderRef jpeg = CGDataProviderCreateWithData ( NULL, g_pData, iImageSize, NULL );
			
			// now we'll decompress the data from jpeg into a raw image
			CGImageRef image = CGImageCreateWithJPEGDataProvider ( jpeg, NULL, false, kCGRenderingIntentDefault );
			
			// free the jpeg data from the conversion as it's no longer required
			CGDataProviderRelease ( jpeg );
			
			// take this image and construct a Texture2D image (which has OpenGL buffers ready)
			[ g_pTexture initWithImage: [ UIImage imageWithCGImage: image ] ];
			
			// release image to keep memory under control :)
			CGImageRelease ( image );
			
			// draw the sprite
			g_pSprite->Draw ( iImageWidth, iImageHeight );
		}

		// feed input activity direct to scraper
		if ( agk::GetPointerPressed()==1 )
		{
			int iRawDataType = 1;
			cNetworkMessage *pRawDataReturnMessage = new cNetworkMessage();
			pRawDataReturnMessage->AddInt( iRawDataType );
			pRawDataReturnMessage->AddFloat( agk::GetPointerX() );
			pRawDataReturnMessage->AddFloat( agk::GetPointerY() );
			g_Network1.SendMessage( 0, pRawDataReturnMessage );
		}
		// and pointer release
		if ( agk::GetPointerReleased()==1 )
		{
			int iRawDataType = 2;
			cNetworkMessage *pRawDataReturnMessage = new cNetworkMessage();
			pRawDataReturnMessage->AddInt( iRawDataType );
			pRawDataReturnMessage->AddFloat( agk::GetPointerX() );
			pRawDataReturnMessage->AddFloat( agk::GetPointerY() );
			g_Network1.SendMessage( 0, pRawDataReturnMessage );
		}		
		// pointer move
		if ( agk::GetPointerState()==1 )
		{
			int iRawDataType = 3;
			cNetworkMessage *pRawDataReturnMessage = new cNetworkMessage();
			pRawDataReturnMessage->AddInt( iRawDataType );
			pRawDataReturnMessage->AddFloat( agk::GetPointerX() );
			pRawDataReturnMessage->AddFloat( agk::GetPointerY() );
			g_Network1.SendMessage( 0, pRawDataReturnMessage );
		}
		// accelerometer
		if ( agk::GetDirectionX() != 0.0f || agk::GetDirectionY() != 0.0f )
		{
			int iRawDataType = 11;
			cNetworkMessage *pRawDataReturnMessage = new cNetworkMessage();
			pRawDataReturnMessage->AddInt( iRawDataType );
			pRawDataReturnMessage->AddFloat( agk::GetDirectionX() );
			pRawDataReturnMessage->AddFloat( agk::GetDirectionY() );
			g_Network1.SendMessage( 0, pRawDataReturnMessage );
		}
	}
	#endif
	
	// refresh screen
	agk::Sync();
}

void app::ScrapperSync ( int iSwapOnly )
{
	#ifdef AGKWINDOWS
	#ifdef SCRAPPERSENDER

	// pick up input data from IOS device
	cNetworkMessage *pMsg = g_Network1.GetMessage();
	while ( pMsg )
	{
		// Windows Host can also RECEIVE raw input data from IOS device
		int iMessageID = pMsg->GetInt();
		if ( iMessageID==1 )
		{
			float fRawDataX = pMsg->GetFloat();
			float fRawDataY = pMsg->GetFloat();
			int iRawDataX = (int)fRawDataX;
			int iRawDataY = (int)fRawDataY;
			agk::MouseMove( 0, iRawDataX, iRawDataY );
			agk::TouchMoved( 1, iRawDataX, iRawDataY );
			agk::MouseLeftButton( 0, 1 );
			agk::TouchPressed( 1, iRawDataX, iRawDataY );
		}
		if ( iMessageID==2 )
		{
			float fRawDataX = pMsg->GetFloat();
			float fRawDataY = pMsg->GetFloat();
			agk::MouseLeftButton( 0, 0 );
			int iRawDataX = (int)fRawDataX;
			int iRawDataY = (int)fRawDataY;
			agk::TouchReleased( 1, iRawDataX, iRawDataY );
		}
		if ( iMessageID==3 )
		{
			float fRawDataX = pMsg->GetFloat();
			float fRawDataY = pMsg->GetFloat();
			agk::MouseMove( 0, (int)fRawDataX, (int)fRawDataY );
			agk::TouchMoved( 1, (int)fRawDataX, (int)fRawDataY );
		}
		if ( iMessageID==11 )
		{
			float fRawAccelDataX = pMsg->GetFloat();
			float fRawAccelDataY = pMsg->GetFloat();
			// force raw data into accelerometer and set accelerometer as 'existing' (iOS device)
			agk::Accelerometer ( fRawAccelDataX, fRawAccelDataY, 0.0f );
		}
		if ( iMessageID==101 )
		{
			if ( g_bAGKViewerMode==false )
			{
				// set Windows player (screen scrapper) to emulate flags of IOS device
				agk::SetMouseExist( false );
				agk::SetJoystickExist( false );
				agk::SetKeyboardExist( false );
				agk::SetMultiTouchExist( true );
				agk::SetAccelerometerExist( true );

				// fake the device name, device width and height
				int iDeviceWidth = pMsg->GetInt();
				int iDeviceHeight = pMsg->GetInt();
				agk::SetFakeDeviceName ( "ios" );
				agk::SetFakeDeviceWidth( iDeviceWidth );
				agk::SetFakeDeviceHeight( iDeviceHeight );

				// oops, the app started thinking it was a Windows app, but in fact
				// it was an emulated iOS app and so the app must be restarted
				g_bResetApp = true;
				g_bAGKViewerMode = true;
				g_dwScrapperTimeOut = 0;

				// immediate exit
				delete pMsg;
				return;
			}
		}
		if ( iMessageID==201 )
		{
			// feed the Windows player a quality setting that can be used to dynamically
			// toggle between fast performance and quality rendering - eventually maybe
		}
		delete pMsg;
		pMsg = g_Network1.GetMessage();
	}

	// leave this scrapper system after five seconds if not started
	if ( g_dwScrapperTimeOut > 0 )
	{
		if ( g_bAGKViewerMode==false )
		{
			if ( timeGetTime() > g_dwScrapperTimeOut + 5000 )
			{
				g_bScrapperActive=false;
				g_Network1.CloseNetwork();
				agk::Sync(); // paul 16-01-12 - must still call a sync or it will be skipped for this frame causing print commands to print twice
				return;
			}
		}
	}

	//
	// scrape screen - this grabs the screen and sends it as a stream to a networked device
	//

	// get a connection
	if ( g_pSocket == NULL )
	{
		// create the socket
		g_pSocket = g_NetworkListener.GetNewConnection ( );

		// 251011 - if we have a socket, needs to be fast and time out after 5 seconds
		// in cases where the receiving device has been cancelled (perminant block)
		//g_pSocket->SetTimeout ( 5 );
	}

	// update and render screen
	if ( iSwapOnly==0 )
	{
		agk::Update();
		agk::Render();
		/*
		// must render exactly like sync but without the swap!
		agk::Update(); // update 2D objects 
		agk::RenderBack(); // draw 2D objects that are behind 3D
		agk::ClearDepthBuffer(); // separate 2D/3D depth buffers
		agk::Render3D(); // draw 3D objects
		agk::ClearDepthBuffer(); // separate 2D/3D depth buffers
		agk::Render(); // draw 2D objects that are in front of 3D
		*/
	}

	// only if AGK Viewer is active
	int iSize = 0;
	char* pFileData = NULL;
	if ( g_bAGKViewerMode==true )
	{
		// resolution	
		if ( g_iAGKViewerOrigWidth==-1 )
		{
			// first original scraped resolution is the one we stick to
			g_iAGKViewerOrigWidth = agk::GetRealDeviceWidth();
			g_iAGKViewerOrigHeight = agk::GetRealDeviceHeight();
		}
		int x = g_iAGKViewerOrigWidth;
		int y = g_iAGKViewerOrigHeight;

		// target resolution (lower the faster, higher the better quality stream)
		int targetwidth = 1024;//160 = lowest
		int targetheight = 1024;//160 = lowest
		int targetquality = 50;//average compression

		// use iOS volume to control the quality of the AGK Viewer (as there is no sound)
		// iOS call to getdevicevolume does not relate to up/down button on iPad.
		//float fPerc = (float)agk::GetDeviceVolume() / 100.0f;
		//targetwidth = (int)((float)targetwidth * fPerc);
		//targetheight = (int)((float)targetheight * fPerc);

		// ensure target is no larger than source
		if ( targetwidth > x/2 ) targetwidth = x/2;
		if ( targetheight > y/2 ) targetheight = y/2;

		// image size (the +1 is for the averaging reads when we anticipate scaling down by x2)
		long imageSize = (x+1) * (y+1) * 3;
		static long lastSize = 0;
		
		// allocate the buffer
		if ( g_pData == NULL || lastSize < imageSize ) 
		{
			if ( g_pData ) delete [] g_pData;
			g_pData = new unsigned char [ imageSize ];
			lastSize = imageSize;
		}

		// read all the pixels in
		glReadPixels ( 0, 0, x, y, GL_RGB, GL_UNSIGNED_BYTE, g_pData );

		// only handles a 2x image reduction
		static unsigned char *m_pDataSmall = new unsigned char[ targetwidth * targetheight * 3 ];

		// reduce from WIDTHxHEIGHT to 160x240
		float fWidthPer = (float)x / (float)targetwidth;
		float fHeightPer = (float)y / (float)targetheight;
		for ( int i = 0; i < targetheight; i++ )
		{
			for ( int j = 0; j < targetwidth; j++ )
			{
				int indexT = i*targetwidth + j;
				float findexS = (j*fWidthPer) + ((int)(i*fHeightPer)*x);
				int indexS = (int)findexS;
				int red = g_pData[ indexS*3 ] + g_pData[ (indexS+1)*3 ] + g_pData[ (indexS+x)*3 ] + g_pData[ (indexS+x+1)*3 ];
				int green = g_pData[ indexS*3 + 1 ] + g_pData[ (indexS+1)*3 + 1 ] + g_pData[ (indexS+x)*3 + 1 ] + g_pData[ (indexS+x+1)*3 + 1 ];
				int blue = g_pData[ indexS*3 + 2 ] + g_pData[ (indexS+1)*3 + 2 ] + g_pData[ (indexS+x)*3 + 2 ] + g_pData[ (indexS+x+1)*3 + 2 ];
				red /= 4;
				green /= 4;
				blue /= 4;

				m_pDataSmall[ indexT*3 ] = red & 0xff;
				m_pDataSmall[ indexT*3 + 1 ] = green & 0xff;
				m_pDataSmall[ indexT*3 + 2 ] = blue & 0xff;
			}
		}

		// new image size
		x = targetwidth;
		y = targetheight;
		
		// convert to a jpeg (uses TEMPORARY OS file, does not flush to disk = performance helper)
		JpegFile jpg;
		char szFileName [ 256 ] = "";
		sprintf ( szFileName, "file.jpg" );
		FILE *outfile = fopen(szFileName, "w+bD");//wb");
		jpg.RGBToJpegFileInMemory ( outfile, m_pDataSmall, x, y, TRUE, targetquality);
		fflush(outfile);
		// now open the jpeg and extract its data
		FILE* fp = outfile;
		fseek ( fp, 0, SEEK_END );
		iSize = ftell ( fp );
		pFileData = new char [ iSize ];
		memset ( pFileData, 0, sizeof ( char ) * iSize );
		rewind ( fp );
		fread ( pFileData, iSize, 1, fp );
		fclose ( fp );

		// if AGK Viewer active (streaming) and detect when
		// socket terminates connection for any reason
		if ( g_pSocket )
		{
			if ( g_pSocket->GetDisconnected()==true )
			{
				PostQuitMessage(0);
			}
		}
	}

	// if we have a socket send data out
	if ( g_pSocket )
	{
		// size and actual data
		g_pSocket->SendInt  ( iSize );
		g_pSocket->SendInt  ( agk::GetRealDeviceWidth() );
		g_pSocket->SendInt  ( agk::GetRealDeviceHeight() );
		g_pSocket->SendData ( pFileData, iSize );
	}

	// clear data from the file
	if ( pFileData ) { delete [ ] pFileData; pFileData=NULL; }

	// show users full screen
	agk::Swap ( );

	// always : gobble all messages to the host
	if ( g_pSocket==NULL )
	{
		if ( timeGetTime() > g_dwBroadcastStreamPing )
		{
			g_dwBroadcastStreamPing = timeGetTime() + 1000;
			cNetworkMessage *pBroadcastMsg = new cNetworkMessage();
			pBroadcastMsg->AddString( "i have stream" );
			g_Network1.SendMessage( 0, pBroadcastMsg );
		}
	}

	#endif
	#endif
}

// Main loop, called every frame
void app::Loop ( void )
{
	/*
	static int prevControlStage = 0;
	if ( prevControlStage != App.g_iAppControlStage )
	{
		uString info;
		info.Format( "Control Stage: %d", App.g_iAppControlStage );
		agk::Warning( info );

		prevControlStage = App.g_iAppControlStage;
	}
	*/

	// intercept if interpreter is 'waiting' for new app
	if ( App.g_iAppControlStage != 0 )
	{
		if ( App.g_iAppControlStage>=1001 && App.g_iAppControlStage<=1999 )
		{
			// new scrapper system - transmits video stream to device, and returns device input data
			ScrapperLoop();
		}
		else
		{
			// standard native execution mode - obtains media and code to run on the device
			WaitingLoop();				
		}
		return;
	}
	
	// main interpreter loop
	#ifndef SCRAPPER
	g_iInstructionCounter = g_iInstructionCounterStart;
	while ( g_iInstructionCounter-- )
	{
		// debug mode : record last instruction (so we can trace back after runtime error)
		// if ( 1 ) RecordForFlashback();

		// remote debugging control system
		// will report current 'program state' and allow remote debugger
		// to control sequence within the interpreter (step by step, go to line, etc)
		// change variables, type data, array data (but not stack position data)
		if ( agk::m_bTriggerBreakPointNow==true )
		{
			// BREAK instruction triggered breakpoint
			agk::m_bTriggerBreakPointNow = false;

			// remote debugger initialises here
			if ( g_bRemoteDebuggingActive==false )
			{
				// the interpreter hosts a network when it starts a new app
				// so any remote debuggers can find it and watch it's bits
				g_DebugNetwork.HostNetwork ( "App Debugger Network", "remote app", 42420 );
				g_bRemoteDebuggingActive = true;
			}
			if ( g_bRemoteDebuggingActive==true )
			{
				if ( g_bRemoteDebuggingInProgress==false )
				{
					// In Remote Debugging Mode, NOP command is a BREAKPOINT for debugger
					g_bRemoteDebuggingInProgress = true;
					g_iRemoteDebuggingMode = 0;
				}
			}
		}
		if ( g_bRemoteDebuggingInProgress==true )
		{
			// always conduct a client clean-up system (debug tools)
			// LEE, this is repeated, use a call instead to re-use code!!
			if ( g_DebugNetwork.IsActive())
			{
				int clientID = g_DebugNetwork.GetFirstClient();
				while ( clientID > 0 )
				{
					if ( g_DebugNetwork.GetClientDisconnected(clientID)==1 )
					{
						g_DebugNetwork.DeleteDisconnectedClient(clientID);
						g_bRemoteDebuggingInProgress = false;
					}
					clientID = g_DebugNetwork.GetNextClient();
				}
			}

			// send debug data from app to debug tool
			cNetworkMessage* pMsg = NULL;
			if ( g_DebugNetwork.IsActive())
			{
				// Temp vars
				int iPacketChunkMax = 10;

				// [1] general stats
				pMsg = new cNetworkMessage;
				pMsg->AddInt(1);
				pMsg->AddInt(g_pByteCodePtr->dwLineNumber);
				g_DebugNetwork.SendMessage(0,pMsg);

				// [2] variable buffer
				int iVarOffset = 0;
				int iVarCount = g_dwVariableBufferSize/4;
				while ( iVarOffset<iVarCount )
				{
					pMsg = new cNetworkMessage;
					int iVarsChunk = iVarCount - iVarOffset;
					if ( iVarsChunk > iPacketChunkMax ) iVarsChunk=iPacketChunkMax;
					pMsg->AddInt(2);
					pMsg->AddInt(iVarOffset);
					pMsg->AddInt(iVarOffset+iVarsChunk);
					for ( int n=iVarOffset; n<iVarOffset+iVarsChunk; n++ )
					{
						pMsg->AddInt(*(int*)((char*)g_pVarBuffer+(n*4)));
						pMsg->AddFloat(*(float*)((char*)g_pVarBuffer+(n*4)));
						if ( g_iDebugVarGlobalStrings && n<g_iDebugVarGlobalStringsMax && g_iDebugVarGlobalStrings[n]==1 )
						{
							LPSTR pStr = *(char**)((char*)g_pVarBuffer+(n*4));
							if ( pStr )
								pMsg->AddString(pStr);
							else
								pMsg->AddString("");
						}
						else
							pMsg->AddString("");
					}
					g_DebugNetwork.SendMessage(0,pMsg);
					iVarOffset+=iVarsChunk;
				}

				// [3] stack nests
				int iStackOffset = 0;
				int iStackCount = g_dwSubroutineStackIndex;
				while ( iStackOffset<iStackCount )
				{
					pMsg = new cNetworkMessage;
					int iStackChunk = iStackCount - iStackOffset;
					if ( iStackChunk > iPacketChunkMax ) iStackChunk=iPacketChunkMax;
					pMsg->AddInt(3);
					pMsg->AddInt(iStackCount); // actual end of stack nest
					pMsg->AddInt(iStackOffset);
					pMsg->AddInt(iStackOffset+iStackChunk);
					for ( int n=iStackOffset; n<iStackOffset+iStackChunk; n++ )
					{
						// work out where this function call jumped to, so we can get
						// the line number and extract the name of the function (smart huh!)
						sByteCode* pUserCall = g_pSubroutineStack[n];
						sByteCode* pFunctionStart = &g_ByteCode[pUserCall->dwP[0] - 1];
						pMsg->AddInt(pFunctionStart->dwLineNumber);
					}
					g_DebugNetwork.SendMessage(0,pMsg);
					iStackOffset+=iStackChunk;
				}

				// [4] stack buffer
				int iStackBufferOffset = 0;
				int tstacksize = ((g_pStackPtr-g_pStack)/4);
				int iStackBufferCount = tstacksize;
				while ( iStackBufferOffset<iStackBufferCount )
				{
					pMsg = new cNetworkMessage;
					int iStackBufferChunk = iStackBufferCount - iStackBufferOffset;
					if ( iStackBufferChunk > iPacketChunkMax ) iStackBufferChunk=iPacketChunkMax;
					pMsg->AddInt(4);
					pMsg->AddInt(iStackBufferOffset);
					pMsg->AddInt(iStackBufferOffset+iStackBufferChunk);
					for ( int n=iStackBufferOffset; n<iStackBufferOffset+iStackBufferChunk; n++ )
					{
						pMsg->AddInt(*(int*)((char*)g_pStack+(n*4)));
						pMsg->AddFloat(*(float*)((char*)g_pStack+(n*4)));
						if ( g_iDebugVarLocalStrings && n<g_iDebugVarLocalStringsMax && g_iDebugVarLocalStrings[n]==1 )
						{
							LPSTR pStr = *(char**)((char*)g_pStack+(n*4));
							if ( pStr )
								pMsg->AddString(pStr);
							else
								pMsg->AddString("");
						}
						else
							pMsg->AddString("");
					}
					g_DebugNetwork.SendMessage(0,pMsg);
					iStackBufferOffset+=iStackBufferChunk;
				}
			}

			// wait for message response from debug tool (step through mode)
			// we are stepping per LINE not per INSTRUCTION (many in one line)
			bool bPauseProgram = true;
			// 1 : stop when not on current line (i.e. next one/last one)
			if ( g_iRemoteDebuggingMode==1 && g_iRemoteDebuggingLastLineRemembered==g_pByteCodePtr->dwLineNumber ) bPauseProgram = false;
			// 2 : stop when on a specific line (exact line number) 
			bool bComeBackInToCheckIfLineChanged = false;
			if ( g_iRemoteDebuggingMode==2 )
			{
				if ( g_iRemoteDebuggingAdvanceToLine!=(int)g_pByteCodePtr->dwLineNumber )
				{
					bComeBackInToCheckIfLineChanged = true;
					bPauseProgram = false;
				}
			}
			// 3 : never stop
			if ( g_iRemoteDebuggingMode==3 ) bPauseProgram = false;
			if ( bPauseProgram==true || bComeBackInToCheckIfLineChanged==true )
			{
				// special mode bComeBackInToCheckIfLineChanged
				// of g_iRemoteDebuggingMode==2 (advance to line)
				// can re-enter when when not in pause mode, to check messages
				// as the debug tool can CHANGE the skip stop line at will
				float fDebugInitPeriod = agk::Timer();
				int iActionID = 0;
				while ( iActionID==0 )
				{
					cNetworkMessage *pMsg = g_DebugNetwork.GetMessage();
					while ( pMsg )
					{
						//uString sSenderName;
						//UINT clientID = pMsg->GetSenderID();
						//g_Network1.GetClientName( clientID, sSenderName );
						iActionID = pMsg->GetInt();
						int iSupportValue = pMsg->GetInt();
						if ( iActionID==42410 ) 
						{
							// create global string variable table
							if ( g_iDebugVarGlobalStrings ) delete [] g_iDebugVarGlobalStrings;
							g_iDebugVarGlobalStringsMax = iSupportValue+1;
							g_iDebugVarGlobalStrings = new int[g_iDebugVarGlobalStringsMax];
							memset ( g_iDebugVarGlobalStrings, 0, g_iDebugVarGlobalStringsMax*sizeof(int) );
							int iStringOffset = pMsg->GetInt();
							while ( iStringOffset!=0 )
							{
								int iOffsetIndex = iStringOffset / 4;
								g_iDebugVarGlobalStrings[iOffsetIndex] = 1;
								iStringOffset = pMsg->GetInt();
							}

							// send signal we are now set-up
							cNetworkMessage* pSendMsg = new cNetworkMessage;
							pSendMsg->AddInt(5);
							g_DebugNetwork.SendMessage(0,pSendMsg);
						}
						if ( iActionID==42411 ) 
						{
							// create local stack string variable table
							if ( g_iDebugVarLocalStrings ) delete [] g_iDebugVarLocalStrings;
							g_iDebugVarLocalStringsMax = iSupportValue+1;
							g_iDebugVarLocalStrings = new int[g_iDebugVarLocalStringsMax];
							memset ( g_iDebugVarLocalStrings, 0, g_iDebugVarLocalStringsMax*sizeof(int) );
							int iStringOffset = pMsg->GetInt();
							while ( iStringOffset!=0 )
							{
								int iOffsetIndex = iStringOffset / 4;
								g_iDebugVarLocalStrings[iOffsetIndex] = 1;
								iStringOffset = pMsg->GetInt();
							}
						}
						if ( iActionID==42412 ) 
						{
							// create array snapshot from request (and send back results)
							cNetworkMessage* pSendMsg = new cNetworkMessage;
							pSendMsg->AddInt(6);
							for ( int n=0; n<iSupportValue; n++ )
							{
								int iVarOffsetToArray = pMsg->GetInt();
								int iArrayDim[10];
								memset ( &iArrayDim, 0, sizeof(iArrayDim) );
								iArrayDim[1] = pMsg->GetInt();
								iArrayDim[2] = pMsg->GetInt();
								if ( iArrayDim[2]==-1 ) iArrayDim[2] = 0;
								iArrayDim[3] = pMsg->GetInt();
								if ( iArrayDim[3]==-1 ) iArrayDim[3] = 0;
								int iUDTOffset = pMsg->GetInt();
								uString sDataType;
								pMsg->GetString(sDataType);
								LPSTR pResult = new char[512];
								sprintf ( pResult, "" ); // android does not have wsprintf

								// access the specified array and return data in string
								g_pArrayPtr = *(char**)((char*)g_pVarBuffer+iVarOffsetToArray);
								if ( g_pArrayPtr==NULL )
								{
									sprintf ( pResult, "n/a" ); // android does not have wsprintf
								}
								else
								{
									DWORD* pArrayHeader = (DWORD*)g_pArrayPtr - 10;
									DWORD* pdwHeaderDimSize = pArrayHeader;
									DWORD dwLatestArrayOffset = 0;
									DWORD dw1stDimension = 1;
									dwLatestArrayOffset += (DWORD)iArrayDim[1] * dw1stDimension;
									for ( DWORD nn=1; nn<=7; nn++ )
									{
										if ( pdwHeaderDimSize[nn] > 0 )
										{
											DWORD dw2ndDimension = 1;
											for ( DWORD n=0; n<nn; n++ )
											{
												if ( pdwHeaderDimSize[n]>0 )
													dw2ndDimension *= pdwHeaderDimSize[n];
												else
													break;
											}
											dwLatestArrayOffset += (DWORD)iArrayDim[1+nn] * dw2ndDimension;
										}
									}
									if ( dwLatestArrayOffset < 0 || dwLatestArrayOffset >= pdwHeaderDimSize[9] )
									{
										sprintf ( pResult, "o/o/b" ); // android does not have wsprintf
									}
									else
									{
										// report UDT name or actual value of 'final datatype'
										strcpy ( pResult, sDataType.GetStr() );
										g_pArrayPtrB = g_pArrayPtr;
										g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*dwLatestArrayOffset) + iUDTOffset ));

                                        /* so I can compile IOS for Rick
										if ( stricmp ( sDataType.GetStr(), "integer" )==NULL )
										// android does not have stricmp
										sDataType.Lower();
										if ( strcmp ( sDataType.GetStr(), "integer" )==NULL )
										{
											sprintf ( pResult, "%d", *(int*)g_pArrayPtrB );
										}
										if ( strcmp ( sDataType.GetStr(), "float" )==NULL )
										{
											sprintf ( pResult, "%f", *(float*)g_pArrayPtrB );
										}
										if ( strcmp ( sDataType.GetStr(), "string" )==NULL )
										{
											sprintf ( pResult, "%s", *(char**)g_pArrayPtrB );
										}
                                         */
									}
								}
								pSendMsg->AddString(pResult);
								delete[] pResult;
							}
							g_DebugNetwork.SendMessage(0,pSendMsg);
							iActionID=0;
						}
						if ( iActionID==42420 ) 
						{
							// step
							g_iRemoteDebuggingMode=1;
							g_iRemoteDebuggingLastLineRemembered = g_pByteCodePtr->dwLineNumber;
						}
						if ( iActionID==42421 )
						{
							// advance to line
							g_iRemoteDebuggingMode=2;
							g_iRemoteDebuggingAdvanceToLine = iSupportValue;
						}
						if ( iActionID==42422 )
						{
							// resume program (end step through)
							g_iRemoteDebuggingMode=3;
							g_bRemoteDebuggingInProgress = false;
						}
						delete pMsg;
						pMsg = g_DebugNetwork.GetMessage();
					}

					// always conduct a client clean-up system (debug tools)
					// here when it would be paused waiting for 
					if ( g_DebugNetwork.IsActive())
					{
						int iCountClients = 0;
						int clientID = g_DebugNetwork.GetFirstClient();
						while ( clientID > 0 )
						{
							iCountClients++;
							if ( g_DebugNetwork.GetClientDisconnected(clientID)==1 )
							{
								g_DebugNetwork.DeleteDisconnectedClient(clientID);
								g_bRemoteDebuggingInProgress = false;
								iActionID = 99;
							}
							clientID = g_DebugNetwork.GetNextClient();
						}
						if ( iCountClients==1 )
						{
							// after three seconds and only one client here, leave BREAK() mode
							if ( agk::Timer() > fDebugInitPeriod+3.0f )
							{
								// instant exit, only one client means
								// we have no debug tool in attendance (avoid freeze!)
								iActionID=-1;

								// also end 'debug mode' as we have debug tool to send data to
								g_iRemoteDebuggingMode=3;
								g_bRemoteDebuggingInProgress = false;
							}
						}
					}

					// can exit without pausing (just seeing if advance to line value changed)
					if ( bComeBackInToCheckIfLineChanged==true )
						iActionID=-1;
				}
			}
		}
        
        // report to output
        if ( g_pByteCodePtr->dwLineNumber>6 )
        {
            int lee=42;
        }

		// process instruction/command
		switch ( g_pByteCodePtr->dwInstruction )
		{
			// updated for 108 to allow INCVAR_OFFSET to use these instructions (previously unsupported INC in FUNCTIONS)
			case AGKI_INCVAR_VARIABLE_INTEGER : inl_handleparams();
				*(int*)g_p[0] = (*(int*)g_p[0])+1; break; 
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += 1; break;
			case AGKI_INCVAR_VARIABLE_INTEGER_VARIABLE_INTEGER : inl_handleparams();
				*(int*)g_p[0] = (*(int*)g_p[0])+(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_INTEGER_VARIABLE_FLOAT : inl_handleparams();
				*(int*)g_p[0] = (*(int*)g_p[0])+(int)(*(float*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_INTEGER_VARIABLE_DWORD : inl_handleparams();
				*(int*)g_p[0] = (*(int*)g_p[0])+(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_INTEGER_VALUE_INTEGER : inl_handleparams();
				*(int*)g_p[0] = (*(int*)g_p[0])+(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)g_pByteCodePtr->iP[1]; break;
			case AGKI_INCVAR_VARIABLE_INTEGER_VALUE_FLOAT : inl_handleparams();
				*(int*)g_p[0] = (*(int*)g_p[0])+(int)(*(float*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)g_pByteCodePtr->fP[1]; break;
			case AGKI_INCVAR_VARIABLE_INTEGER_VALUE_DWORD : inl_handleparams();
				*(int*)g_p[0] = (*(int*)g_p[0])+(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)g_pByteCodePtr->dwP[1]; break;

			case AGKI_INCVAR_VARIABLE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += 1; break;
			case AGKI_INCVAR_VARIABLE_DWORD_VARIABLE_INTEGER :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += *(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_DWORD_VARIABLE_FLOAT :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_DWORD_VARIABLE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_DWORD_VALUE_INTEGER :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)g_pByteCodePtr->iP[1]; break;
			case AGKI_INCVAR_VARIABLE_DWORD_VALUE_FLOAT :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)g_pByteCodePtr->fP[1]; break;
			case AGKI_INCVAR_VARIABLE_DWORD_VALUE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (int)g_pByteCodePtr->dwP[1]; break;

			case AGKI_INCVAR_VARIABLE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) + 1.0f; break; 
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += 1.0f; break;
			case AGKI_INCVAR_VARIABLE_FLOAT_VARIABLE_INTEGER : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) + (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (float)*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) + (*(float*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += *(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_FLOAT_VARIABLE_DWORD : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) + (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (float)*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_INCVAR_VARIABLE_FLOAT_VALUE_INTEGER : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) + (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (float)g_pByteCodePtr->iP[1]; break;
			case AGKI_INCVAR_VARIABLE_FLOAT_VALUE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) + (*(float*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += g_pByteCodePtr->fP[1]; break;
			case AGKI_INCVAR_VARIABLE_FLOAT_VALUE_DWORD : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) + (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) += (float)g_pByteCodePtr->dwP[1]; break;

			// updated for 108 to allow DECVAR_OFFSET to use these instructions (previously unsupported DEC in FUNCTIONS)
			case AGKI_DECVAR_VARIABLE_INTEGER : inl_handleparams(); 
				*(int*)g_p[0] = (*(int*)g_p[0])-1; break; 
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= 1; break;
			case AGKI_DECVAR_VARIABLE_INTEGER_VARIABLE_INTEGER : inl_handleparams(); 
				*(int*)g_p[0] = (*(int*)g_p[0])-(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_INTEGER_VARIABLE_FLOAT : inl_handleparams(); 
				*(int*)g_p[0] = (*(int*)g_p[0])-(int)(*(float*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_INTEGER_VARIABLE_DWORD : inl_handleparams(); 
				*(int*)g_p[0] = (*(int*)g_p[0])-(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_INTEGER_VALUE_INTEGER : inl_handleparams(); 
				*(int*)g_p[0] = (*(int*)g_p[0])-(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)g_pByteCodePtr->iP[1]; break;
			case AGKI_DECVAR_VARIABLE_INTEGER_VALUE_FLOAT : inl_handleparams(); 
				*(int*)g_p[0] = (*(int*)g_p[0])-(int)(*(float*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)g_pByteCodePtr->fP[1]; break;
			case AGKI_DECVAR_VARIABLE_INTEGER_VALUE_DWORD : inl_handleparams(); 
				*(int*)g_p[0] = (*(int*)g_p[0])-(*(int*)g_p[1]); break;
				//*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)g_pByteCodePtr->dwP[1]; break;

			case AGKI_DECVAR_VARIABLE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= 1; break;
			case AGKI_DECVAR_VARIABLE_DWORD_VARIABLE_INTEGER :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= *(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_DWORD_VARIABLE_FLOAT :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_DWORD_VARIABLE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_DWORD_VALUE_INTEGER :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)g_pByteCodePtr->iP[1]; break;
			case AGKI_DECVAR_VARIABLE_DWORD_VALUE_FLOAT :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)g_pByteCodePtr->fP[1]; break;
			case AGKI_DECVAR_VARIABLE_DWORD_VALUE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (int)g_pByteCodePtr->dwP[1]; break;

			case AGKI_DECVAR_VARIABLE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) - 1.0f; break; 
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= 1.0f; break;
			case AGKI_DECVAR_VARIABLE_FLOAT_VARIABLE_INTEGER : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) - (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (float)*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) - (*(float*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= *(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_FLOAT_VARIABLE_DWORD : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) - (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (float)*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); break;
			case AGKI_DECVAR_VARIABLE_FLOAT_VALUE_INTEGER : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) - (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (float)g_pByteCodePtr->iP[1]; break;
			case AGKI_DECVAR_VARIABLE_FLOAT_VALUE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) - (*(float*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= g_pByteCodePtr->fP[1]; break;
			case AGKI_DECVAR_VARIABLE_FLOAT_VALUE_DWORD : inl_handleparams();
				*(float*)g_p[0] = (*(float*)g_p[0]) - (float)(*(int*)g_p[1]); break;
				//*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) -= (float)g_pByteCodePtr->dwP[1]; break;

			case AGKI_MATH_MUL : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA * dwB;
			}
			break;
			case AGKI_MATH_DIV : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				if ( dwB==0 )
					*(int*)g_p[2] = 0;
				else
					*(int*)g_p[2] = dwA / dwB;
			}
			break;
			case AGKI_MATH_ADD : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA + dwB;
			}
			break;
			case AGKI_MATH_SUB : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA - dwB;
			}
			break;
			case AGKI_MATH_MOD : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA % dwB;
			}
			break;
			case AGKI_MATH_SHR : inl_handleparams();
			{
				DWORD dwA = *(DWORD*)g_p[0];
				DWORD dwB = *(DWORD*)g_p[1];
				*(DWORD*)g_p[2] = dwA >> dwB;
			}
			break;
			case AGKI_MATH_SHL : inl_handleparams();
			{
				DWORD dwA = *(DWORD*)g_p[0];
				DWORD dwB = *(DWORD*)g_p[1];
				*(DWORD*)g_p[2] = dwA << dwB;
			}
			break;
			case AGKI_MATH_OR : inl_handleparams();
			{
				DWORD dwA = *(DWORD*)g_p[0];
				DWORD dwB = *(DWORD*)g_p[1];
				//*(DWORD*)g_p[2] = dwA || dwB;
				*(DWORD*)g_p[2] = dwA | dwB; // 280811 - change to bitwise OR (should not affect conditions)
			}
			break;
			case AGKI_MATH_XOR : inl_handleparams();
			{
				DWORD dwA = *(DWORD*)g_p[0];
				DWORD dwB = *(DWORD*)g_p[1];
				*(DWORD*)g_p[2] = dwA ^ dwB; // 280811 - bitwise XOR
			}
			break;
			case AGKI_MATH_BITNOT : inl_handleparams();
			{
				DWORD dwA = *(DWORD*)g_p[0];
				//DWORD dwB = *(DWORD*)g_p[1];
				//*(DWORD*)g_p[2] = 1 - dwA;
				*(DWORD*)g_p[2] = ~dwA; // 071011 - bitwise NOT
			}
			break;
			case AGKI_MATH_AND : inl_handleparams();
			{
				DWORD dwA = *(DWORD*)g_p[0];
				DWORD dwB = *(DWORD*)g_p[1];
				*(DWORD*)g_p[2] = dwA & dwB;
			}
			break;
			case AGKI_MATH_NOT : inl_handleparams();
			{
				DWORD dwA = *(DWORD*)g_p[0];
				//DWORD dwB = *(DWORD*)g_p[1];
				//*(DWORD*)g_p[2] = 1 - dwA;
				*(DWORD*)g_p[2] = dwA; // 071011 - IF NOT already toggles condition, so we dont do anything here
			}
			break;
			case AGKI_MATH_EQUAL : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA == dwB;
			}
			break;
			case AGKI_MATH_NOTEQUAL : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA != dwB;
			}
			break;
			case AGKI_MATH_GREATER : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA > dwB;
			}
			break;
			case AGKI_MATH_GREATEREQUAL : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA >= dwB;
			}
			break;
			case AGKI_MATH_LESS : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA < dwB;
			}
			break;
			case AGKI_MATH_LESSEQUAL : inl_handleparams();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA <= dwB;
			}
			break;

			// Lee, need to complete this after MeeGO approved (and check all string = string assignments too)
			/*
			case AGKI_POWERLLL_VARIABLE_INTEGER_VALUE_INTEGER_VALUE_INTEGER : inl_handleparam();
			{
				int dwA = *(int*)g_p[0];
				int dwB = *(int*)g_p[1];
				*(int*)g_p[2] = dwA ^ dwB;
			}
			*/

			case AGKI_EQUALLFF_VARIABLE_INTEGER_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
			{
				float fA = *(float*)g_p[1];
				float fB = *(float*)g_p[2];
				*(int*)g_p[0] = fA == fB;
			}
			break;
			case AGKI_NOTEQUALLFF_VARIABLE_INTEGER_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
			{
				float fA = *(float*)g_p[1];
				float fB = *(float*)g_p[2];
				*(int*)g_p[0] = fA != fB;
			}
			break;
			case AGKI_GREATERLFF_VARIABLE_INTEGER_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
			{
				float fA = *(float*)g_p[1];
				float fB = *(float*)g_p[2];
				*(int*)g_p[0] = fA > fB;
			}
			break;
			case AGKI_GREATEREQUALLFF_VARIABLE_INTEGER_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
			{
				float fA = *(float*)g_p[1];
				float fB = *(float*)g_p[2];
				*(int*)g_p[0] = fA >= fB;
			}
			break;
			case AGKI_LESSLFF_VARIABLE_INTEGER_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
			{
				float fA = *(float*)g_p[1];
				float fB = *(float*)g_p[2];
				*(int*)g_p[0] = fA < fB;
			}
			break;
			case AGKI_LESSEQUALLFF_VARIABLE_INTEGER_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
			{
				float fA = *(float*)g_p[1];
				float fB = *(float*)g_p[2];
				*(int*)g_p[0] = fA <= fB;
			}
			break;

			case AGKI_EQUALLSS_VARIABLE_INTEGER_VARIABLE_STRING_VARIABLE_STRING :
			case AGKI_EQUALLSS_VARIABLE_INTEGER_VALUE_STRING_VALUE_STRING : inl_handleparams();
			{
				char* fA = *(char**)g_p[1];
				char* fB = *(char**)g_p[2];
				if ( fA==0 ) fA=(LPSTR)"";
				if ( fB==0 ) fB=(LPSTR)"";
				if ( strcmp ( fA, fB )==0 )
					*(int*)g_p[0] = 1;
				else
					*(int*)g_p[0] = 0;
			}
			break;
			case AGKI_NOTEQUALLSS_VARIABLE_INTEGER_VALUE_STRING_VALUE_STRING :
			case AGKI_NOTEQUALLSS_VARIABLE_INTEGER_VARIABLE_STRING_VARIABLE_STRING : inl_handleparams();
			{
				char* fA = *(char**)g_p[1];
				char* fB = *(char**)g_p[2];
				if ( fA==0 ) fA=(LPSTR)"";
				if ( fB==0 ) fB=(LPSTR)"";
				if ( strcmp ( fA, fB )!=0 )
					*(int*)g_p[0] = 1;
				else
					*(int*)g_p[0] = 0;
			}
			break;
			case AGKI_GREATERLSS_VARIABLE_INTEGER_VARIABLE_STRING_VARIABLE_STRING :
			case AGKI_GREATERLSS_VARIABLE_INTEGER_VALUE_STRING_VALUE_STRING : inl_handleparams();
			{
				char* fA = *(char**)g_p[1];
				char* fB = *(char**)g_p[2];
				if ( fA==0 ) fA=(LPSTR)"";
				if ( fB==0 ) fB=(LPSTR)"";
				if ( strcmp ( fA, fB )>0 )
					*(int*)g_p[0] = 1;
				else
					*(int*)g_p[0] = 0;
			}
			break;
			case AGKI_GREATEREQUALLSS_VARIABLE_INTEGER_VARIABLE_STRING_VARIABLE_STRING : 
			case AGKI_GREATEREQUALLSS_VARIABLE_INTEGER_VALUE_STRING_VALUE_STRING : inl_handleparams();
			{
				char* fA = *(char**)g_p[1];
				char* fB = *(char**)g_p[2];
				if ( fA==0 ) fA=(LPSTR)"";
				if ( fB==0 ) fB=(LPSTR)"";
				if ( strcmp ( fA, fB )>=0 )
					*(int*)g_p[0] = 1;
				else
					*(int*)g_p[0] = 0;
			}
			break;
			case AGKI_LESSLSS_VARIABLE_INTEGER_VARIABLE_STRING_VARIABLE_STRING :
			case AGKI_LESSLSS_VARIABLE_INTEGER_VALUE_STRING_VALUE_STRING : inl_handleparams();
			{
				char* fA = *(char**)g_p[1];
				char* fB = *(char**)g_p[2];
				if ( fA==0 ) fA=(LPSTR)"";
				if ( fB==0 ) fB=(LPSTR)"";
				if ( strcmp ( fA, fB )<0 )
					*(int*)g_p[0] = 1;
				else
					*(int*)g_p[0] = 0;
			}
			break;
			case AGKI_LESSEQUALLSS_VARIABLE_INTEGER_VARIABLE_STRING_VARIABLE_STRING :
			case AGKI_LESSEQUALLSS_VARIABLE_INTEGER_VALUE_STRING_VALUE_STRING : inl_handleparams();
			{
				char* fA = *(char**)g_p[1];
				char* fB = *(char**)g_p[2];
				if ( fA==0 ) fA=(LPSTR)"";
				if ( fB==0 ) fB=(LPSTR)"";
				if ( strcmp ( fA, fB )<=0 )
					*(int*)g_p[0] = 1;
				else
					*(int*)g_p[0] = 0;
			}
			break;

			case AGKI_MULFFF_VARIABLE_FLOAT_VALUE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = *(float*)g_p[1] * *(float*)g_p[2];
			break;
			case AGKI_DIVFFF_VARIABLE_FLOAT_VALUE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = *(float*)g_p[1] / *(float*)g_p[2];
			break;
			case AGKI_ADDFFF_VARIABLE_FLOAT_VALUE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = *(float*)g_p[1] + *(float*)g_p[2];
			break;
			case AGKI_SUBFFF_VARIABLE_FLOAT_VALUE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = *(float*)g_p[1] - *(float*)g_p[2];
			break;

			case AGKI_ADDSSS_VARIABLE_STRING_VARIABLE_STRING_VARIABLE_STRING : 
			{
				// 180811 - if src blank, provide empty string
				inl_handleparams();
				LPSTR pSrcStr = (char*)*(char**)g_p[1];
				if ( pSrcStr==NULL ) pSrcStr="";
				if ( pSrcStr!=NULL )
					if ( (char*)*(char**)g_p[2]!=NULL )
					{
						// string to add
						if ( (char*)*(char**)g_p[0] ) delete[] (char*)*(char**)g_p[0];
						DWORD dwStringLength = strlen(pSrcStr)+strlen((char*)*(char**)g_p[2]);
						char** lvalue = (char**)g_p[0];
						*lvalue = new char[dwStringLength+1];
						strcpy ( (char*)*(char**)g_p[0], pSrcStr );
						strcat ( (char*)*(char**)g_p[0], (char*)*(char**)g_p[2] );
					}
					else
					{
						// simple copy
						if ( (char*)*(char**)g_p[0] ) delete[] (char*)*(char**)g_p[0];
						DWORD dwStringLength = strlen(pSrcStr);
						char** lvalue = (char**)g_p[0];
						*lvalue = new char[dwStringLength+1];
						strcpy ( (char*)*(char**)g_p[0], pSrcStr );
					}
			}
			break;

			case AGKI_POWERLLL_VARIABLE_INTEGER_VARIABLE_INTEGER_VARIABLE_INTEGER : inl_handleparams();
				*(int*)g_p[0] = (int)pow((float)*(int*)g_p[1],*(int*)g_p[2]);
				break;
			case AGKI_POWERFFF_VARIABLE_FLOAT_VARIABLE_FLOAT_VARIABLE_FLOAT : inl_handleparams();
				*(float*)g_p[0] = powf(*(float*)g_p[1],(*(float*)g_p[2]));
				break;
			case AGKI_POWERDDD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD : inl_handleparams();
				*(DWORD*)g_p[0] = (DWORD)pow((float)*(DWORD*)g_p[1],(int)*(DWORD*)g_p[2]);
				break;

			case AGKI_ASSIGNVAR_VARIABLE_INTEGER_VARIABLE_INTEGER :
				*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->iP[1]); 
			break;
			case AGKI_ASSIGNVAR_VARIABLE_INTEGER_VALUE_INTEGER :
				*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = g_pByteCodePtr->iP[1];
			break;
			case AGKI_ASSIGNVAR_VARIABLE_INTEGER_OFFSET_INTEGER : 
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(int*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_VARIABLE_INTEGER_ARRAY_INTEGER : 
			{
				inl_handleparam_g_12();
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(int*)g_pArrayPtrB;
			}
			break;
			case AGKI_ASSIGNVAR_VARIABLE_FLOAT_VARIABLE_FLOAT :
				*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); 
			break;
			case AGKI_ASSIGNVAR_VARIABLE_FLOAT_VALUE_FLOAT :
				*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = g_pByteCodePtr->fP[1]; 
			break;
			case AGKI_ASSIGNVAR_VARIABLE_FLOAT_OFFSET_FLOAT :
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(float*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_VARIABLE_FLOAT_ARRAY_FLOAT : inl_handleparam_g_12();
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(float*)g_pArrayPtrB;
			break;
			case AGKI_ASSIGNVAR_VARIABLE_DWORD_VARIABLE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]); 
			break;
			case AGKI_ASSIGNVAR_VARIABLE_DWORD_VALUE_DWORD :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = (int)g_pByteCodePtr->dwP[1];
			break;
			case AGKI_ASSIGNVAR_VARIABLE_DWORD_OFFSET_DWORD :
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(DWORD*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_VARIABLE_DWORD_ARRAY_DWORD : inl_handleparam_g_12();
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = *(DWORD*)g_pArrayPtrB;
			break;

			case AGKI_ASSIGNVAR_OFFSET_INTEGER_VARIABLE_INTEGER :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(int*)g_pStackLocationA = *(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->iP[1]); 
			break;
			case AGKI_ASSIGNVAR_OFFSET_INTEGER_VALUE_INTEGER :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(int*)g_pStackLocationA = g_pByteCodePtr->iP[1];
			break;
			case AGKI_ASSIGNVAR_OFFSET_INTEGER_OFFSET_INTEGER :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(int*)g_pStackLocationA = *(int*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_OFFSET_INTEGER_ARRAY_INTEGER : inl_handleparam_g_12();
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(int*)g_pStackLocationA = *(int*)g_pArrayPtrB;
			break;
			case AGKI_ASSIGNVAR_OFFSET_FLOAT_VARIABLE_FLOAT :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(int*)g_pStackLocationA = *(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->iP[1]); 
			break;
			case AGKI_ASSIGNVAR_OFFSET_FLOAT_VALUE_FLOAT :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(float*)g_pStackLocationA = g_pByteCodePtr->fP[1];
			break;
			case AGKI_ASSIGNVAR_OFFSET_FLOAT_OFFSET_FLOAT :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(float*)g_pStackLocationA = *(float*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_OFFSET_FLOAT_ARRAY_FLOAT : inl_handleparam_g_12();
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(float*)g_pStackLocationA = *(float*)g_pArrayPtrB;
			break;
			case AGKI_ASSIGNVAR_OFFSET_DWORD_VARIABLE_DWORD :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(DWORD*)g_pStackLocationA = *(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->iP[1]); 
			break;
			case AGKI_ASSIGNVAR_OFFSET_DWORD_VALUE_DWORD :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(DWORD*)g_pStackLocationA = g_pByteCodePtr->dwP[1];
			break;
			case AGKI_ASSIGNVAR_OFFSET_DWORD_OFFSET_DWORD :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(DWORD*)g_pStackLocationA = *(DWORD*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_OFFSET_DWORD_ARRAY_DWORD : inl_handleparam_g_12();
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(DWORD*)g_pStackLocationA = *(DWORD*)g_pArrayPtrB;
			break;

			case AGKI_ASSIGNVAR_ARRAY_INTEGER_VARIABLE_INTEGER : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				*(int*)g_pArrayPtr = *(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);
			break;
			case AGKI_ASSIGNVAR_ARRAY_INTEGER_VALUE_INTEGER : 
			{
				inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				*((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] )) = g_pByteCodePtr->iP[1];
			}
			break;
			case AGKI_ASSIGNVAR_ARRAY_INTEGER_OFFSET_INTEGER : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(int*)g_pArrayPtr = *(int*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_ARRAY_INTEGER_ARRAY_INTEGER : inl_handleparam_g_11(); inl_handleparam_g_12();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] )); 
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(int*)g_pArrayPtr = *(int*)g_pArrayPtrB;
			break;
			case AGKI_ASSIGNVAR_ARRAY_FLOAT_VARIABLE_FLOAT : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				*(float*)g_pArrayPtr = *(float*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);
			break;
			case AGKI_ASSIGNVAR_ARRAY_FLOAT_VALUE_FLOAT : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				*(float*)g_pArrayPtr = g_pByteCodePtr->fP[1];
			break;
			case AGKI_ASSIGNVAR_ARRAY_FLOAT_OFFSET_FLOAT : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(float*)g_pArrayPtr = *(float*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_ARRAY_FLOAT_ARRAY_FLOAT : inl_handleparam_g_11(); inl_handleparam_g_12();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(float*)g_pArrayPtr = *(float*)g_pArrayPtrB;
			break;
			case AGKI_ASSIGNVAR_ARRAY_STRING_VARIABLE_STRING : 
			{
				// copy variable string into array string
				inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				LPSTR pSrcStr = *(LPSTR*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);

				// paul - 290512 - delete string to fix mem leak
				if ( *(LPSTR*)g_pArrayPtr!=NULL ) delete [] *(LPSTR*)g_pArrayPtr;

				if ( pSrcStr==0 )
				{
					LPSTR pBlank = new char[1];
					*(LPSTR*)g_pArrayPtr = pBlank;
					pBlank[0]=0;
				}	
				else
				{
					LPSTR pNewString = new char[strlen(pSrcStr)+1];
					strcpy ( pNewString, pSrcStr );
					*(LPSTR*)g_pArrayPtr = pNewString;
				}
			}
			break;
			case AGKI_ASSIGNVAR_ARRAY_STRING_VALUE_STRING :
			{
				// copy value string into array string
				inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				//LPSTR pSrcStr = *static_cast<LPSTR*>((void*)g_pLiteralString[g_pByteCodePtr->dwP[1]]);
				LPSTR pSrcStr = 0;
				if ( g_pByteCodePtr->iP[1]>=0 ) pSrcStr = g_pLiteralString[g_pByteCodePtr->iP[1]];
				// lee - 160412 - ensure old array strings are deleted (avoid memory leak)
				if ( *(LPSTR*)g_pArrayPtr!=NULL ) delete [] *(LPSTR*)g_pArrayPtr;
				if ( pSrcStr==0 )
				{
					LPSTR pBlank = new char[1];
					*(LPSTR*)g_pArrayPtr = pBlank;
					pBlank[0]=0;
				}	
				else
				{
					LPSTR pNewString = new char[strlen(pSrcStr)+1];
					strcpy ( pNewString, pSrcStr );
					*(LPSTR*)g_pArrayPtr = pNewString;
				}
			}
			break;
			case AGKI_ASSIGNVAR_ARRAY_STRING_OFFSET_STRING : inl_handleparam_g_11();
				// copy offset string into array string
				//g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				//g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				//g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				//*(float*)g_pArrayPtr = *(float*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_ARRAY_STRING_ARRAY_STRING : inl_handleparam_g_11(); inl_handleparam_g_12();
				// copy array string into array string
				//g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				//g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				//g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				//g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				//*(float*)g_pArrayPtr = *(float*)g_pArrayPtrB;
			break;
			case AGKI_ASSIGNVAR_ARRAY_DWORD_VARIABLE_DWORD : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				*(DWORD*)g_pArrayPtr = *(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);
			break;
			case AGKI_ASSIGNVAR_ARRAY_DWORD_VALUE_DWORD : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				*(DWORD*)g_pArrayPtr = g_pByteCodePtr->dwP[1];
			break;
			case AGKI_ASSIGNVAR_ARRAY_DWORD_OFFSET_DWORD : inl_handleparam_g_11();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(DWORD*)g_pArrayPtr = *(DWORD*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_ARRAY_DWORD_ARRAY_DWORD : inl_handleparam_g_11(); inl_handleparam_g_12();
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				*(DWORD*)g_pArrayPtr = *(DWORD*)g_pArrayPtrB;
			break;

			// Lee, need to complete this after MeeGO approved (and check all string = string assignments too)
			/*
			case AGKI_ASSIGNVAR_ARRAY_STRING_VARIABLE_STRING : inl_handleparam_g_11();
			{
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				char* pSrcStr = *(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);
				char* pDestStrArray = *(DWORD*)g_pArrayPtr;
				pSrcStr = pSrcStr;
				pDestStrArray = pDestStrArray;
			}
			break;
			case AGKI_ASSIGNVAR_ARRAY_STRING_VALUE_STRING : inl_handleparam_g_11();
//				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
//				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
//				*(DWORD*)g_pArrayPtr = g_pByteCodePtr->dwP[1];
			break;
			case AGKI_ASSIGNVAR_STRING_DWORD_OFFSET_STRING : inl_handleparam_g_11();
//				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
//				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
//				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
//				*(DWORD*)g_pArrayPtr = *(DWORD*)g_pStackLocationB;
			break;
			case AGKI_ASSIGNVAR_STRING_DWORD_ARRAY_STRING : inl_handleparam_g_11(); inl_handleparam_g_12();
//				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
//				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
//				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
//				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
//				*(DWORD*)g_pArrayPtr = *(DWORD*)g_pArrayPtrB;
			break;
			*/

			case AGKI_ASSIGNVAR_USERDATATYPE_USERDATATYPE:
			{
				// As assignments are only two params, we pass the UDT size into the third parameter
				DWORD dwUDTSize = g_pByteCodePtr->dwP[2];

				// clear user type with zeros (size stored in offset field)
				// 030312 - does not determine local UDT usage at all
				// so instead use the dwPOffset[0] = -12345 which the compiler sets when its a local
				// if ( g_pByteCodePtr->iP[0]>0 )
				if ( g_pByteCodePtr->dwPOffset[0]!=-12345 )
				{
					// global UDT
					if ( g_pByteCodePtr->dwPOffset[1]==0 )
					{
						// clear
						char* pVarPtr = (char*)g_pVarBuffer + g_pByteCodePtr->dwP[0];
						memset ( pVarPtr, 0, dwUDTSize );
					}
					else
					{
						// copy one UDT to the other
						char* pVarPtrA = (char*)g_pVarBuffer + g_pByteCodePtr->dwP[0];
						char* pVarPtrB = (char*)g_pVarBuffer + g_pByteCodePtr->dwP[1];
						memcpy ( pVarPtrA, pVarPtrB, dwUDTSize );
					}
				}
				else
				{
					// local UDT
					if ( g_pByteCodePtr->dwPOffset[1]==0 )
					{
						// clear
						g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->iP[0];
						memset ( (DWORD*)g_pStackLocationA, 0, dwUDTSize );
					}
					else
					{
						// copy one UDT to the other
						g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->iP[0];
						g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->iP[1];
						memcpy ( (DWORD*)g_pStackLocationA, (DWORD*)g_pStackLocationB, dwUDTSize );
					}
				}
			}
			break;
			case AGKI_COPYBYTEMEMORY_VALUE_DWORD_USERDATATYPE_USERDATATYPE:
			{
				char *pVarPtrA, *pVarPtrB;
				DWORD dwUDTSize = g_pByteCodePtr->dwP[0];
				if ( dwUDTSize>0 )
				{
					if ( g_pByteCodePtr->dwPOffset[2]!=-12345 )
					{
						// global UDT copy one UDT to the other
						if ( g_pByteCodePtr->cPType[2]==40 )
						{
							// 100612 - build1077 - account for offset for UDT=UDT command (g_pByteCodePtr->dwPOffset[2])
							pVarPtrA = (char*)g_pVarBuffer + g_pByteCodePtr->dwP[2] + g_pByteCodePtr->dwPOffset[2];
						}
						else
						{
							inl_handleparam_g_13();
							g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[2]);
							DWORD dwElementPosInType = g_pByteCodePtr->dwPOffset[2];
							DWORD dwSubscript = *(DWORD*)g_p[11+2];
							DWORD dwSizeOfArrayElement = *(DWORD*)((DWORD*)g_pArrayPtr-2);
							DWORD dwFinalOffsetIntoEntireArray = (dwSubscript * dwSizeOfArrayElement) + dwElementPosInType;
							dwFinalOffsetIntoEntireArray/=sizeof(DWORD);
							pVarPtrA = (char*)((DWORD*)g_pArrayPtr+dwFinalOffsetIntoEntireArray);
						}
					}
					else
					{
						// local UDT
						// build 1077 =  + g_pByteCodePtr->dwPOffset[2]
						// build 108X = insane, this is -12345 and not needed in local UDT!
						pVarPtrA = g_pStackPtrEBP + g_pByteCodePtr->iP[2];// + g_pByteCodePtr->dwPOffset[2];
					}
					if ( g_pByteCodePtr->dwPOffset[1]!=-12345 )
					{
						if ( g_pByteCodePtr->cPType[1]==40 )
						{
							// 100612 - build1077 - account for offset for UDT=UDT command (g_pByteCodePtr->dwPOffset[1])
							pVarPtrB = (char*)g_pVarBuffer + g_pByteCodePtr->dwP[1] + g_pByteCodePtr->dwPOffset[1];
						}
						else
						{
							inl_handleparam_g_12();
							g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
							g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
							pVarPtrB = (char*)(DWORD*)g_pArrayPtr;
						}
					}
					else
					{
						// local UDT
						// build 1077 =  + g_pByteCodePtr->dwPOffset[1]
						// build 108X = insane, this is -12345 and not needed in local UDT!
						pVarPtrB = g_pStackPtrEBP + g_pByteCodePtr->iP[1];// + g_pByteCodePtr->dwPOffset[1];
					}

					// 180811 - fixed memcpy, it was copying dest into src!?!?
					memcpy ( pVarPtrB, pVarPtrA, dwUDTSize );
				}
			}
			break;

			case AGKI_JUMPIFFALSE : inl_handleparams();
				if ( *(int*)g_p[1]==0 )
				{
					g_pByteCodePtr = &g_ByteCode[g_pByteCodePtr->dwP[0] - 1];
				}
			break;
			case AGKI_JUMPIFTRUE : inl_handleparams();
				if ( *(int*)g_p[1]!=0 )
				{
					g_pByteCodePtr = &g_ByteCode[g_pByteCodePtr->dwP[0] - 1];
				}
			break;

			case AGKI_CASTLTOD_VARIABLE_DWORD_VARIABLE_INTEGER :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = (DWORD)*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);
			break;
			case AGKI_CASTLTOD_VARIABLE_DWORD_VALUE_INTEGER :
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = (DWORD)g_pByteCodePtr->iP[1];
			break;
			case AGKI_CASTLTOD_VARIABLE_DWORD_OFFSET_INTEGER :
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = (DWORD)*(int*)g_pStackLocationB;
			break;
			case AGKI_CASTLTOD_VARIABLE_DWORD_ARRAY_INTEGER :
			{
				switch( g_pByteCodePtr->cPType[11+1] )
				{
					case AGKP_VALUE_INTEGER : g_p[11+1] = (char*)&g_pByteCodePtr->iP[11+1]; break;
					case AGKP_VALUE_DWORD : g_p[11+1] = (char*)&g_pByteCodePtr->dwP[11+1]; break;
					case AGKP_VARIABLE_INTEGER : g_p[11+1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->dwP[11+1]); break;
					case AGKP_VARIABLE_DWORD : g_p[11+1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->dwP[11+1]); break;
					case AGKP_OFFSET_INTEGER : g_p[11+1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->iP[11+1]); break;
					case AGKP_OFFSET_DWORD : g_p[11+1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->iP[11+1]); break;
				}
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				DWORD dwValue = (DWORD)*((int*)g_pArrayPtr);
				*(DWORD*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[0]+g_pByteCodePtr->dwP[0]) = dwValue;
			}
			break;
			case AGKI_CASTLTOD_OFFSET_DWORD_VARIABLE_INTEGER :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(DWORD*)g_pStackLocationA = (DWORD)*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);
			break;
			case AGKI_CASTLTOD_OFFSET_DWORD_VALUE_INTEGER :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(DWORD*)g_pStackLocationA = (DWORD)g_pByteCodePtr->iP[1];
			break;
			case AGKI_CASTLTOD_OFFSET_DWORD_OFFSET_INTEGER :
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(DWORD*)g_pStackLocationA = (DWORD)*(int*)g_pStackLocationB;
			break;
			case AGKI_CASTLTOD_OFFSET_DWORD_ARRAY_INTEGER :
			{
				switch( g_pByteCodePtr->cPType[11+1] )
				{
					case AGKP_VALUE_INTEGER : g_p[11+1] = (char*)&g_pByteCodePtr->iP[11+1]; break;
					case AGKP_VALUE_DWORD : g_p[11+1] = (char*)&g_pByteCodePtr->dwP[11+1]; break;
					case AGKP_VARIABLE_INTEGER : g_p[11+1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->dwP[11+1]); break;
					case AGKP_VARIABLE_DWORD : g_p[11+1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->dwP[11+1]); break;
					case AGKP_OFFSET_INTEGER : g_p[11+1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->iP[11+1]); break;
					case AGKP_OFFSET_DWORD : g_p[11+1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->iP[11+1]); break;
				}
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				DWORD dwValue = (DWORD)*((int*)g_pArrayPtr);
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0];
				*(DWORD*)g_pStackLocationA = dwValue;
			}
			break;
			case AGKI_CASTLTOD_ARRAY_DWORD_VARIABLE_INTEGER :
			{
				switch( g_pByteCodePtr->cPType[11+0] )
				{
					case AGKP_VALUE_INTEGER : g_p[11+0] = (char*)&g_pByteCodePtr->iP[11+0]; break;
					case AGKP_VALUE_DWORD : g_p[11+0] = (char*)&g_pByteCodePtr->dwP[11+0]; break;
					case AGKP_VARIABLE_INTEGER : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_VARIABLE_DWORD : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_OFFSET_INTEGER : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
					case AGKP_OFFSET_DWORD : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
				}
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				*((DWORD*)g_pArrayPtr) = (DWORD)*(int*)((char*)g_pVarBuffer+g_pByteCodePtr->dwPOffset[1]+g_pByteCodePtr->dwP[1]);
			}
			break;
			case AGKI_CASTLTOD_ARRAY_DWORD_VALUE_INTEGER :
			{
				switch( g_pByteCodePtr->cPType[11+0] )
				{
					case AGKP_VALUE_INTEGER : g_p[11+0] = (char*)&g_pByteCodePtr->iP[11+0]; break;
					case AGKP_VALUE_DWORD : g_p[11+0] = (char*)&g_pByteCodePtr->dwP[11+0]; break;
					case AGKP_VARIABLE_INTEGER : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_VARIABLE_DWORD : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_OFFSET_INTEGER : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
					case AGKP_OFFSET_DWORD : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
				}
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				*((DWORD*)g_pArrayPtr) = (DWORD)g_pByteCodePtr->iP[1];
			}
			break;
			case AGKI_CASTLTOD_ARRAY_DWORD_OFFSET_INTEGER :
			{
				switch( g_pByteCodePtr->cPType[11+0] )
				{
					case AGKP_VALUE_INTEGER : g_p[11+0] = (char*)&g_pByteCodePtr->iP[11+0]; break;
					case AGKP_VALUE_DWORD : g_p[11+0] = (char*)&g_pByteCodePtr->dwP[11+0]; break;
					case AGKP_VARIABLE_INTEGER : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_VARIABLE_DWORD : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_OFFSET_INTEGER : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
					case AGKP_OFFSET_DWORD : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
				}
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1];
				*((DWORD*)g_pArrayPtr) = (DWORD)*(int*)g_pStackLocationB;
			}
			break;
			case AGKI_CASTLTOD_ARRAY_DWORD_ARRAY_INTEGER :
			{
				switch( g_pByteCodePtr->cPType[11+0] )
				{
					case AGKP_VALUE_INTEGER : g_p[11+0] = (char*)&g_pByteCodePtr->iP[11+0]; break;
					case AGKP_VALUE_DWORD : g_p[11+0] = (char*)&g_pByteCodePtr->dwP[11+0]; break;
					case AGKP_VARIABLE_INTEGER : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_VARIABLE_DWORD : g_p[11+0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->dwP[11+0]); break;
					case AGKP_OFFSET_INTEGER : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
					case AGKP_OFFSET_DWORD : g_p[11+0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+0] + g_pByteCodePtr->iP[11+0]); break;
				}
				g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
				switch( g_pByteCodePtr->cPType[11+1] )
				{
					case AGKP_VALUE_INTEGER : g_p[11+1] = (char*)&g_pByteCodePtr->iP[11+1]; break;
					case AGKP_VALUE_DWORD : g_p[11+1] = (char*)&g_pByteCodePtr->dwP[11+1]; break;
					case AGKP_VARIABLE_INTEGER : g_p[11+1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->dwP[11+1]); break;
					case AGKP_VARIABLE_DWORD : g_p[11+1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->dwP[11+1]); break;
					case AGKP_OFFSET_INTEGER : g_p[11+1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->iP[11+1]); break;
					case AGKP_OFFSET_DWORD : g_p[11+1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+1] + g_pByteCodePtr->iP[11+1]); break;
				}
				g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[1]);
				g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+1])) + g_pByteCodePtr->dwPOffset[1] ));
				DWORD dwValue = (DWORD)*((int*)g_pArrayPtrB);
				*((DWORD*)g_pArrayPtr) = dwValue;
			}
			break;

			case AGKI_CASTLTOF_VARIABLE_FLOAT_VARIABLE_INTEGER : 
			case AGKI_CASTLTOF_VARIABLE_FLOAT_VALUE_INTEGER : 
			case AGKI_CASTLTOF_VARIABLE_FLOAT_OFFSET_INTEGER : 
			case AGKI_CASTLTOF_VARIABLE_FLOAT_ARRAY_INTEGER : 
			case AGKI_CASTLTOF_OFFSET_FLOAT_VARIABLE_INTEGER : 
			case AGKI_CASTLTOF_OFFSET_FLOAT_VALUE_INTEGER : 
			case AGKI_CASTLTOF_OFFSET_FLOAT_OFFSET_INTEGER : 
			case AGKI_CASTLTOF_OFFSET_FLOAT_ARRAY_INTEGER : 
			case AGKI_CASTLTOF_ARRAY_FLOAT_VARIABLE_INTEGER : 
			case AGKI_CASTLTOF_ARRAY_FLOAT_VALUE_INTEGER : 
			case AGKI_CASTLTOF_ARRAY_FLOAT_OFFSET_INTEGER : 
			case AGKI_CASTLTOF_ARRAY_FLOAT_ARRAY_INTEGER : 
				inl_handleparams();
				*(float*)g_p[0] = (float)*(int*)g_p[1];
			break;

			case AGKI_CASTFTOL_VARIABLE_INTEGER_VARIABLE_FLOAT : 
			case AGKI_CASTFTOL_VARIABLE_INTEGER_VALUE_FLOAT : 
			case AGKI_CASTFTOL_VARIABLE_INTEGER_OFFSET_FLOAT : 
			case AGKI_CASTFTOL_VARIABLE_INTEGER_ARRAY_FLOAT : 
			case AGKI_CASTFTOL_OFFSET_INTEGER_VARIABLE_FLOAT : 
			case AGKI_CASTFTOL_OFFSET_INTEGER_VALUE_FLOAT : 
			case AGKI_CASTFTOL_OFFSET_INTEGER_OFFSET_FLOAT : 
			case AGKI_CASTFTOL_OFFSET_INTEGER_ARRAY_FLOAT : 
			case AGKI_CASTFTOL_ARRAY_INTEGER_VARIABLE_FLOAT : 
			case AGKI_CASTFTOL_ARRAY_INTEGER_VALUE_FLOAT : 
			case AGKI_CASTFTOL_ARRAY_INTEGER_OFFSET_FLOAT : 
			case AGKI_CASTFTOL_ARRAY_INTEGER_ARRAY_FLOAT : 
				inl_handleparams();
				*(int*)g_p[0] = agk::Round(*(float*)g_p[1]);
			break;

			case AGKI_CASTFTOD_VARIABLE_DWORD_VARIABLE_FLOAT : 
			case AGKI_CASTFTOD_VARIABLE_DWORD_VALUE_FLOAT : 
			case AGKI_CASTFTOD_VARIABLE_DWORD_OFFSET_FLOAT : 
			case AGKI_CASTFTOD_VARIABLE_DWORD_ARRAY_FLOAT : 
			case AGKI_CASTFTOD_OFFSET_DWORD_VARIABLE_FLOAT : 
			case AGKI_CASTFTOD_OFFSET_DWORD_VALUE_FLOAT : 
			case AGKI_CASTFTOD_OFFSET_DWORD_OFFSET_FLOAT : 
			case AGKI_CASTFTOD_OFFSET_DWORD_ARRAY_FLOAT : 
			case AGKI_CASTFTOD_ARRAY_DWORD_VARIABLE_FLOAT : 
			case AGKI_CASTFTOD_ARRAY_DWORD_VALUE_FLOAT : 
			case AGKI_CASTFTOD_ARRAY_DWORD_OFFSET_FLOAT : 
			case AGKI_CASTFTOD_ARRAY_DWORD_ARRAY_FLOAT : 
				inl_handleparams();
				*(DWORD*)g_p[0] = (DWORD)agk::Round(*(float*)g_p[1]);
			break;

			case AGKI_CASTDTOL_VARIABLE_INTEGER_VARIABLE_DWORD : 
			case AGKI_CASTDTOL_VARIABLE_INTEGER_VALUE_DWORD : 
			case AGKI_CASTDTOL_VARIABLE_INTEGER_OFFSET_DWORD : 
			case AGKI_CASTDTOL_VARIABLE_INTEGER_ARRAY_DWORD : 
			case AGKI_CASTDTOL_OFFSET_INTEGER_VARIABLE_DWORD : 
			case AGKI_CASTDTOL_OFFSET_INTEGER_VALUE_DWORD : 
			case AGKI_CASTDTOL_OFFSET_INTEGER_OFFSET_DWORD : 
			case AGKI_CASTDTOL_OFFSET_INTEGER_ARRAY_DWORD : 
			case AGKI_CASTDTOL_ARRAY_INTEGER_VARIABLE_DWORD : 
			case AGKI_CASTDTOL_ARRAY_INTEGER_VALUE_DWORD : 
			case AGKI_CASTDTOL_ARRAY_INTEGER_OFFSET_DWORD : 
			case AGKI_CASTDTOL_ARRAY_INTEGER_ARRAY_DWORD : 
				inl_handleparams();
				*(int*)g_p[0] = (int)*(DWORD*)g_p[1];
			break;

			case AGKI_CASTDTOF_VARIABLE_FLOAT_VARIABLE_DWORD : 
			case AGKI_CASTDTOF_VARIABLE_FLOAT_VALUE_DWORD : 
			case AGKI_CASTDTOF_VARIABLE_FLOAT_OFFSET_DWORD : 
			case AGKI_CASTDTOF_VARIABLE_FLOAT_ARRAY_DWORD : 
			case AGKI_CASTDTOF_OFFSET_FLOAT_VARIABLE_DWORD : 
			case AGKI_CASTDTOF_OFFSET_FLOAT_VALUE_DWORD : 
			case AGKI_CASTDTOF_OFFSET_FLOAT_OFFSET_DWORD : 
			case AGKI_CASTDTOF_OFFSET_FLOAT_ARRAY_DWORD : 
			case AGKI_CASTDTOF_ARRAY_FLOAT_VARIABLE_DWORD : 
			case AGKI_CASTDTOF_ARRAY_FLOAT_VALUE_DWORD : 
			case AGKI_CASTDTOF_ARRAY_FLOAT_OFFSET_DWORD : 
			case AGKI_CASTDTOF_ARRAY_FLOAT_ARRAY_DWORD : 
				inl_handleparams();
				*(float*)g_p[0] = (float)*(DWORD*)g_p[1];
			break;

			case AGKI_EQUATESS_VARIABLE_STRING_VARIABLE_STRING : inl_handleparams();
			{
				// 0 - return ptr
				// 1 - str to delete
				// 2 - str to copy from (src)
				if ( g_p[1] )
				{
					if ( (char*)*(char**)g_p[1]==NULL )
					{
						if ( g_p[2] )
						{
							if ( (char*)*(char**)g_p[2]!=NULL )
							{
								DWORD dwStringLength = strlen((char*)*(char**)g_p[2]);
								char* pNewStr = new char[dwStringLength+1];
								strcpy ( pNewStr, (char*)*(char**)g_p[2] );
								*(char**)g_p[0] = pNewStr;
							}
						}
					}
					else
					{
						if ( g_p[2] )
						{
							if ( (char*)*(char**)g_p[2]!=NULL )
							{
								delete[] *(char**)g_p[1];
								DWORD dwStringLength = strlen((char*)*(char**)g_p[2]);
								char* pNewStr = new char[dwStringLength+1];
								strcpy ( pNewStr, (char*)*(char**)g_p[2] );
								*(char**)g_p[0] = pNewStr;
							}
						}
					}
				}
			}
			break;
			case AGKI_FREESS_VARIABLE_STRING : inl_handleparams();
			{
				if ( g_p[0] )
				{
					if ( (char*)*(char**)g_p[0]!=NULL )
					{
                        int iC = (int)*(char**)g_p[0];
						if ( iC < 10000 )
                        {
                            // iOS tries to release a string with a pointer of 0x01 ?!? (lee,110512)
                        }
                        else
                            delete[] *(char**)g_p[0];
						*(char**)g_p[0] = NULL;
					}
				}
			}
			break;
			case AGKI_DIRECTJUMP :
				// AGKP_VALUE_DWORD implied ( -1 to counter end of function advance)
				g_pByteCodePtr = &g_ByteCode[g_pByteCodePtr->dwP[0] - 1];
			break;
			case AGKI_PUSHSTACK :
			{
				// current function (needed if we are pushing new items to the stack from inside a user function)
				g_pStackPtrCurrentEBP = g_pStackPtrEBP;

				// this will fill up the stack with all the parameters from this byte code instruction
				g_pStackPtrEBP = g_pStackPtr;

				// which works on the PC using this code..
				int iParamIndex = 0;
				if ( 1 )
				{
					switch ( g_pByteCodePtr->cPType[iParamIndex] )
					{
						case AGKP_OFFSET_INTEGER : 
						case AGKP_OFFSET_FLOAT : 
						case AGKP_OFFSET_STRING : 
						case AGKP_OFFSET_DWORD :
						{
							*(DWORD*)g_pStackPtrEBP = (DWORD)((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0]); break;
						}
						break;
						case AGKP_USERDATATYPE: 
						{
							// return UDT
							*(DWORD*)g_pStackPtrEBP = (DWORD)(((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->dwP[0]));
						}
						break;
						case AGKP_USERDATATYPE_OFFSET:
						{
							// return UDT in stack function
							*(DWORD*)g_pStackPtrEBP = (DWORD)(((char*)g_pStackPtrCurrentEBP + 0 + g_pByteCodePtr->iP[iParamIndex]) );
							break;
						}
						case AGKP_USERDATATYPE_ARRAY: 
						{
							// return UDT inside array 
							inl_handleparam_g_11();
							g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
							DWORD dwElementPosInType = g_pByteCodePtr->dwPOffset[0];
							DWORD dwSubscript = *(DWORD*)g_p[11];
							DWORD dwSizeOfArrayElement = *(DWORD*)((DWORD*)g_pArrayPtr-2);
							DWORD dwFinalOffsetIntoEntireArray = (dwSubscript * dwSizeOfArrayElement) + dwElementPosInType;
							dwFinalOffsetIntoEntireArray/=sizeof(DWORD);
							*(DWORD*)g_pStackPtrEBP = (DWORD)(((char*)((DWORD*)g_pArrayPtr+dwFinalOffsetIntoEntireArray)));
						}
						break;
						default:
						{
							// return variable
							*(DWORD*)g_pStackPtrEBP = (DWORD)(((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->dwP[0]));
						}
						break;
					}
					g_pStackPtrEBP+=4;
				}
				iParamIndex++;

				// now function params
				while ( g_pByteCodePtr->cPType[iParamIndex]>0 && iParamIndex<10 )
				{
					// add to stack
					switch ( g_pByteCodePtr->cPType[iParamIndex] )
					{
						case AGKP_VARIABLE_INTEGER : *(int*)g_pStackPtrEBP = *(int*)((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->dwP[iParamIndex]);	break;
						case AGKP_VARIABLE_FLOAT : *(float*)g_pStackPtrEBP = *(float*)((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->dwP[iParamIndex]);	break;
						case AGKP_VARIABLE_STRING : *(DWORD*)g_pStackPtrEBP = *(DWORD*)((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->dwP[iParamIndex]); break;
						case AGKP_VARIABLE_DWORD : *(DWORD*)g_pStackPtrEBP = *(DWORD*)((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->dwP[iParamIndex]); break;
						case AGKP_VALUE_INTEGER : *(int*)g_pStackPtrEBP = g_pByteCodePtr->iP[iParamIndex];	break;
						case AGKP_VALUE_FLOAT : *(float*)g_pStackPtrEBP = g_pByteCodePtr->fP[iParamIndex];	break;
						case AGKP_VALUE_STRING : *(DWORD*)g_pStackPtrEBP = (DWORD)static_cast<DWORD*>((void*)g_pLiteralString[g_pByteCodePtr->dwP[iParamIndex]]); break;
						case AGKP_VALUE_DWORD : *(DWORD*)g_pStackPtrEBP = g_pByteCodePtr->dwP[iParamIndex]; break;
						case AGKP_OFFSET_INTEGER : *(int*)g_pStackPtrEBP = *(int*)((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->iP[iParamIndex]); break;
						case AGKP_OFFSET_FLOAT : *(float*)g_pStackPtrEBP = *(float*)((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->iP[iParamIndex]); break;
						case AGKP_OFFSET_STRING : *(DWORD*)g_pStackPtrEBP = *(DWORD*)((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->iP[iParamIndex]); break;
						case AGKP_OFFSET_DWORD : *(DWORD*)g_pStackPtrEBP = *(DWORD*)((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->iP[iParamIndex]); break;

						case AGKP_ARRAY_INTEGER : 
							inl_handleparam_g_11_index(iParamIndex);
							g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[iParamIndex]);
							g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+iParamIndex])) + g_pByteCodePtr->dwPOffset[iParamIndex] ));
							*(int*)g_pStackPtrEBP = *(int*)g_pArrayPtrB;
							break;
						case AGKP_ARRAY_FLOAT : 
							inl_handleparam_g_11_index(iParamIndex);
							g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[iParamIndex]);
							g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+iParamIndex])) + g_pByteCodePtr->dwPOffset[iParamIndex] ));
							*(float*)g_pStackPtrEBP = *(float*)g_pArrayPtrB;
							break;
						case AGKP_ARRAY_STRING : 
							inl_handleparam_g_11_index(iParamIndex);
							g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[iParamIndex]);
							g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+iParamIndex])) + g_pByteCodePtr->dwPOffset[iParamIndex] ));
							*(LPSTR*)g_pStackPtrEBP = *(LPSTR*)g_pArrayPtrB;
							break;
						case AGKP_ARRAY_DWORD : 
							inl_handleparam_g_11_index(iParamIndex);
							g_pArrayPtrB = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[iParamIndex]);
							g_pArrayPtrB = (char*)((int*)(g_pArrayPtrB+((*((DWORD*)g_pArrayPtrB-2))*(*(DWORD*)g_p[11+iParamIndex])) + g_pByteCodePtr->dwPOffset[iParamIndex] ));
							*(DWORD*)g_pStackPtrEBP = *(DWORD*)g_pArrayPtrB;
							break;

						case AGKP_USERDATATYPE : 
						{
							// copy UDT from X to X (GLOBAL VAR TABLE)
							DWORD dwUDTSize = g_pByteCodePtr->dwPSize[iParamIndex];
							memcpy ( (DWORD*)g_pStackPtrEBP, (DWORD*)((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->dwP[iParamIndex]), dwUDTSize );
							g_pStackPtrEBP+=(dwUDTSize-4);
							break;//180811 - fix
						}
						case AGKP_USERDATATYPE_OFFSET:
						{
							// copy UDT from X to X (LOCAL STACK UDT)
							DWORD dwUDTSize = g_pByteCodePtr->dwPSize[iParamIndex];
							//offset in UDT used to flag if UDT is local or global (-12345=local)
							//memcpy ( (DWORD*)g_pStackPtrEBP, (DWORD*)((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[iParamIndex] + g_pByteCodePtr->iP[iParamIndex]), dwUDTSize );
							memcpy ( (DWORD*)g_pStackPtrEBP, (DWORD*)((char*)g_pStackPtrCurrentEBP + 0 + g_pByteCodePtr->iP[iParamIndex]), dwUDTSize );
							g_pStackPtrEBP+=(dwUDTSize-4);
							break;
						}
						case AGKP_USERDATATYPE_ARRAY : 
						{
							// copy UDT array from X to X
							if ( iParamIndex==0 ) inl_handleparam_g_11();
							if ( iParamIndex==1 ) inl_handleparam_g_12();
							if ( iParamIndex==2 ) inl_handleparam_g_13();
							g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[iParamIndex]);
							DWORD dwElementPosInType = g_pByteCodePtr->dwPOffset[iParamIndex];
							DWORD dwSubscript = *(DWORD*)g_p[11+iParamIndex];
							DWORD dwSizeOfArrayElement = *(DWORD*)((DWORD*)g_pArrayPtr-2);
							DWORD dwFinalOffsetIntoEntireArray = (dwSubscript * dwSizeOfArrayElement) + dwElementPosInType;
							dwFinalOffsetIntoEntireArray/=sizeof(DWORD);
							DWORD dwSpecificUDTSize = g_pByteCodePtr->dwPSize[iParamIndex];//array type and type passed in could be different (i.e. master[5].lee)
							memcpy ( (DWORD*)g_pStackPtrEBP, (((char*)((DWORD*)g_pArrayPtr+dwFinalOffsetIntoEntireArray))), dwSpecificUDTSize );
							g_pStackPtrEBP+=(dwSpecificUDTSize-4);
						}
						break;
					}

					// next
					g_pStackPtrEBP+=4;
					iParamIndex++;
				}

				// 171011 - users not expecting local vars to have old-data from previous stack activity
				// so we will record the last passed-in data here, then we will wipe the data when we call
				// a function so that all local variables are reset to zero on each call
				// performance hit but will produce more predictable behaviour for T1 users
				g_pStackPtrStartOfLocalVarMemBlock = g_pStackPtrEBP;

				// stack EBP for AGK is set at return param position (start of stack block)
				g_pStackPtrEBP = g_pStackPtr;
			}
			break;
			case AGKI_ASSIGNRETURNVAR : inl_handleparams();
				// copy contents from return param stack location to return variable
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->iP[0];
				*(DWORD*)(*(DWORD*)g_pStackLocationA) = *(DWORD*)g_p[1];
			break;
			case AGKI_ASSIGNRETURNUDT :
				g_pStackLocationA = g_pStackPtrEBP + g_pByteCodePtr->iP[0]; // address to actual return var (not data itself)
				g_pStackLocationB = g_pStackPtrEBP + g_pByteCodePtr->iP[1];
				// need a memcpy here to copy entire UDT data structure into result ptr
				memcpy ( (DWORD*)(*(DWORD*)g_pStackLocationA), (DWORD*)g_pStackLocationB, g_pByteCodePtr->dwPOffset[1] );
			break;
			case AGKI_PULLSTACK :
				g_pStackPtr-=g_pByteCodePtr->dwP[0];
				if ( g_pStackPtr < g_pStack )
					g_pStackPtr = g_pStack;
			break;
			case AGKI_DIRECTJUMPSUBROUTINE :
				g_pSubroutineStack[g_dwSubroutineStackIndex] = g_pByteCodePtr;
				g_pSubroutineStackEBPStore[g_dwSubroutineStackIndex] = g_pStackPtrEBP;
				g_pByteCodePtr = &g_ByteCode[g_pByteCodePtr->dwP[0] - 1];
				g_dwSubroutineStackIndex++;
				if ( g_dwSubroutineStackIndex > g_dwSubroutineStackMax )
					g_dwSubroutineStackIndex = g_dwSubroutineStackMax;
			break;
			case AGKI_DIRECTJUMPUSERFUNCTION :
			{
				// 171011 - before we start running user function code, we need to wipe
				// out local variable space data to keep expectation for T1 users lean
				// (see above PUSHSTACK for more details and g_pStackPtrStartOfLocalVarMemBlock assignment)
				if ( g_pStackPtrStartOfLocalVarMemBlock )
				{
					DWORD dwNumberOfPassedInVars = g_pStackPtrStartOfLocalVarMemBlock - g_pStackPtr;
					DWORD dwNumberOfLocalVarBytesToClear = g_pByteCodePtr->dwP[1] - dwNumberOfPassedInVars;
					memset ( g_pStackPtr + dwNumberOfPassedInVars, 0, dwNumberOfLocalVarBytesToClear );
				}

				// also advance stack pointer to account for size user function
				g_pStackPtr += g_pByteCodePtr->dwP[1];

				// expand stack if required (leave room for the 'next' push stack
				if ( g_pStackPtr > g_pStackEnd-1024 )
				{
					DWORD dwOffset = g_pStackPtr-g_pStack;
					DWORD dwEBPOffset = g_pStackPtrEBP-g_pStack;
					char* pNewStack = new char[g_dwStackMax*2];
					memset ( pNewStack, 0, g_dwStackMax*2 ); // 171011 - clear function stack (as users expect local vars to be zero!!)
					memcpy ( pNewStack, g_pStack, g_dwStackMax );
					delete[] g_pStack;
					g_dwStackMax *= 2;
					g_pStack = pNewStack;
					g_pStackPtr = g_pStack + dwOffset;
					g_pStackPtrEBP = g_pStack + dwEBPOffset;
					g_pStackEnd = g_pStack + g_dwStackMax;
				}

				// record so can RETurn back
				g_pSubroutineStack[g_dwSubroutineStackIndex] = g_pByteCodePtr;
				g_dwSubroutineStackIndex++;
				if ( g_dwSubroutineStackIndex > g_dwSubroutineStackMax )
					g_dwSubroutineStackIndex = g_dwSubroutineStackMax;

				// store EBP ptr with nested function for return procedure
				g_pSubroutineStackEBPStore[g_dwSubroutineStackIndex] = g_pStackPtrEBP;

				// finally, perform jump
				g_pByteCodePtr = &g_ByteCode[g_pByteCodePtr->dwP[0] - 1];
			}
			break;
			case AGKI_RETURNFROMSUBROUTINE :
                if ( g_dwSubroutineStackIndex > 0 )
                {
                    g_dwSubroutineStackIndex--;
                    g_pByteCodePtr = g_pSubroutineStack[g_dwSubroutineStackIndex]; // end of switch will advance ptr for us
                    g_pStackPtrEBP = g_pSubroutineStackEBPStore[g_dwSubroutineStackIndex];
                }
                else
                {
                    // keep program ptr here until quits out (meego?)
                    g_pByteCodePtr--;
                    g_iInstructionCounter = 0;
                    AppQuitNow();
                }
				break;
			case AGKI_EARLYEND :
				g_iInstructionCounter = 0;
				AppQuitNow();
				break;
			case AGKI_QUIT :
				g_iInstructionCounter = 0;
				AppQuitNow();
                break;
			case AGKI_DIMDDD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD_VARIABLE_DWORD: inl_handleparams();
			{
				// passed in type information
				DWORD dwSizeOfOneDataItem = *(DWORD*)g_p[1];
				dwSizeOfOneDataItem = dwSizeOfOneDataItem/4096;
				//DWORD dwTypeValueOfOneDataItem = *(DWORD*)g_p[1]-(dwSizeOfOneDataItem*4096);
				DWORD dwD1 = 1 + *(DWORD*)g_p[2];
				DWORD dwD2 = *(DWORD*)g_p[3]; if ( dwD2 > 0 ) dwD2+=1;
				DWORD dwD3 = *(DWORD*)g_p[4]; if ( dwD3 > 0 ) dwD3+=1;
				DWORD dwD4 = *(DWORD*)g_p[5]; if ( dwD4 > 0 ) dwD4+=1;
				DWORD dwD5 = *(DWORD*)g_p[6]; if ( dwD5 > 0 ) dwD5+=1;
				DWORD dwD6 = *(DWORD*)g_p[7]; if ( dwD6 > 0 ) dwD6+=1;
				DWORD dwD7 = *(DWORD*)g_p[8]; if ( dwD7 > 0 ) dwD7+=1;
				DWORD dwD8 = *(DWORD*)g_p[9]; if ( dwD8 > 0 ) dwD8+=1;

				// Work out array size (can be no bigger than DWORD)
				LONGLONG iiSize = dwD1;
				if(dwD2>0) iiSize *= dwD2;
				if(dwD3>0) iiSize *= dwD3;
				if(dwD4>0) iiSize *= dwD4;
				if(dwD5>0) iiSize *= dwD5;
				if(dwD6>0) iiSize *= dwD6;
				if(dwD7>0) iiSize *= dwD7;
				if(dwD8>0) iiSize *= dwD8;
				iiSize *= dwSizeOfOneDataItem;
				DWORD dwSizeOfArray = (DWORD)iiSize;
				if(dwSizeOfArray==iiSize)
				{
					// create array
					DWORD dwSizeOfHeader = 40;
					char* pArrayPtr = new char[dwSizeOfArray+dwSizeOfHeader];
					memset ( pArrayPtr, 0, dwSizeOfArray+dwSizeOfHeader );
					*((DWORD*)pArrayPtr+0) = dwD1;//*(DWORD*)g_p[2];
					*((DWORD*)pArrayPtr+1) = dwD2;//*(DWORD*)g_p[3];
					*((DWORD*)pArrayPtr+2) = dwD3;//*(DWORD*)g_p[4];
					*((DWORD*)pArrayPtr+3) = dwD4;//*(DWORD*)g_p[5];
					*((DWORD*)pArrayPtr+4) = dwD5;//*(DWORD*)g_p[6];
					*((DWORD*)pArrayPtr+5) = dwD6;//*(DWORD*)g_p[7];
					*((DWORD*)pArrayPtr+6) = dwD7;//*(DWORD*)g_p[8];
					*((DWORD*)pArrayPtr+7) = dwD8;//*(DWORD*)g_p[9];
					*((DWORD*)pArrayPtr+8) = dwSizeOfOneDataItem;
					*((DWORD*)pArrayPtr+9) = dwSizeOfArray / sizeof(DWORD);

					// if array already exists, record it
					char* pOldArray = NULL;
					char* pOldPtr = *(char**)g_p[0];
					if ( *(char**)g_p[0] ) pOldArray = (char*)((DWORD*)(pOldPtr)-10);

					// assign new array
					*(char**)g_p[0] = (char*)((DWORD*)pArrayPtr+10);

					// if old array existed, copy any data that fits into new array
					if ( pOldArray )
					{
						// work out size of datas
						DWORD dwOldSize = *((DWORD*)pOldArray+9);
						DWORD dwNewSize = *((DWORD*)pArrayPtr+9);
						
						// amount to copy over
						DWORD dwCopyOver = dwOldSize;
						if ( dwNewSize < dwOldSize ) dwCopyOver = dwNewSize;

						// memcpy
						char* pOldArrayData = pOldPtr;
						char* pNewArrayData = (char*)((DWORD*)pArrayPtr+10);
						memcpy ( pNewArrayData, pOldArrayData, dwCopyOver * sizeof(DWORD) );

						// now delete old array
						delete[] pOldArray;
					}
				}
				else
				{
					agk::Error ( "Array is too large" );
					g_iInstructionCounter = 0;
					*(char**)g_p[0] = 0;
				}
			}																																																   
			break;
			case AGKI_UNDIMDD_VARIABLE_DWORD_VARIABLE_DWORD: inl_handleparams();
			{
				char** pArrInVarTable = (char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
				g_pArrayPtr = *pArrInVarTable;
				if ( g_pArrayPtr )
				{
					char* pRealArrayStartPtr = (char*)((DWORD*)g_pArrayPtr-10);
					if ( pRealArrayStartPtr )
					{
						// delete old array
						delete[] pRealArrayStartPtr;
						pRealArrayStartPtr=NULL;

						// erase array from variable table
						*pArrInVarTable = NULL;
					}
				}
			}
			break;
			case AGKI_ARRAY_CALC_OFFSET: inl_clearparams(); inl_handleparams();
			{
				// [retdword] [arrayptr] [subscripts sequence]
				g_pArrayPtr = *(char**)g_p[1];

				// no array created, runtime error now
				if ( g_pArrayPtr==NULL )
				{
					agk::Error ( "Array does not exist" );
					g_iInstructionCounter = 0;
					break;
				}

				// header pointer
				//DWORD dwSizeOfHeader = 40;
				DWORD* pArrayHeader = (DWORD*)g_pArrayPtr - 10;

				// work out final array offset from multi-dimentional subscripts (and array header which stores dimension sizes)
				DWORD* pdwHeaderDimSize = pArrayHeader;

				// accumilate offset
				DWORD dwLatestArrayOffset = 0;

				// first dimension (accounts for size of 2nd dimenion onwards)
				DWORD dw1stDimension = 1;
				dwLatestArrayOffset += *(DWORD*)g_p[2] * dw1stDimension;

				// second dimension (accounts for size of 3rd dimenion onwards)
				for ( DWORD nn=1; nn<=7; nn++ )
				{
					if ( pdwHeaderDimSize[nn] > 0 )
					{
						DWORD dw2ndDimension = 1;
						for ( DWORD n=0; n<nn; n++ )
						{
							if ( pdwHeaderDimSize[n]>0 )
								dw2ndDimension *= pdwHeaderDimSize[n];
							else
								break;
						}

						// 050312 - where user accesses large multi-dim array with fewer subscripts
						if ( g_p[2+nn]==NULL )
						{
							agk::Error ( "Array accessed with too few subscripts" );
							g_iInstructionCounter = 0;
							dwLatestArrayOffset = 0;
							break;
						}
						else
							dwLatestArrayOffset += *(DWORD*)g_p[2+nn] * dw2ndDimension;
					}
				}

				// error check (is subscripts within size of this array) (final offset check quicker!)
				if ( dwLatestArrayOffset < 0 || dwLatestArrayOffset >= pdwHeaderDimSize[9] )
				{
					// report run-time error!
					agk::Error ( "Subscript is out of bounds" );
					g_iInstructionCounter = 0;
					dwLatestArrayOffset = 0;
				}

				// final offset passed to $Dx for use as final array subscript offset
				*(DWORD*)g_p[0] = dwLatestArrayOffset;
			}
			break;

			case AGKI_SYNCREAL :
			{
				g_iInstructionCounterStart = 1000000;
				g_iInstructionCounter = 0;

				// FPS
				g_iFrameCount++;
				g_lTimer = 0; //timeGetTime(); // PAUL, can we have agk::Timer() which returns 1 ms counts, thanks
				if ( g_lTimer > g_lLastTimer + 1000 )
				{
					// one second has passed
					g_lLastTimer = g_lTimer;
					g_fScreenFPS = (float)g_iFrameCount;
					g_iFrameCount = 0;
				}

				// sync every time we call it
				if ( g_bScrapperActive==true )
					app::ScrapperSync(0);
				else
					agk::Sync();
			}
			break;
			case AGKI_SWAPREAL:
			{
				g_iInstructionCounterStart = 1000000;
				g_iInstructionCounter = 0;

				// FPS
				g_iFrameCount++;
				g_lTimer = 0; //timeGetTime(); // PAUL, can we have agk::Timer() which returns 1 ms counts, thanks
				if ( g_lTimer > g_lLastTimer + 1000 )
				{
					// one second has passed
					g_lLastTimer = g_lTimer;
					g_fScreenFPS = (float)g_iFrameCount;
					g_iFrameCount = 0;
				}

				// swap every time we call it
				if ( g_bScrapperActive==true )
					app::ScrapperSync(1);
				else
					agk::Swap();
			}
			break;

			//
			// Real Script Commands
			//
			ALL_AGK_CASES_DEFINE

			// Fall Off End
			default:
			{
				// Unknown command passed to interpreter
				sprintf ( g_pNumToString, "Unknown Instruction %d", g_pByteCodePtr->dwInstruction );
				agk::Error ( g_pNumToString );
				g_iInstructionCounter = 0;
				AppQuitNow();
				break;
			}
		}

		// increment instruction ptr
		g_pByteCodePtr++;
	}
	#endif

	// 201011 - detect app reset flag
	#ifdef AGKWINDOWS
	if ( g_bResetApp==true )
	{
		// close old app down, and reload it as though from scratch (as damn it)
		g_bResetApp=false;
		CloseApp();
		SetCurrentDirectory ( g_pOriginalRootDir );
		agk::RestoreWriteDir();
        
		#ifdef AGKWINDOWS
		// T1 BASIC for Windows uses a fixed MEDIA folder (used to be in engine for 1.0.2.8)
		agk::SetCurrentDir ( "media" );
		#endif
        
		// tried to reset entire InitGL cascade but too intricate - no need for this though at present
		// load app again
		LoadApp();
		// simply reset the program pre
		g_pByteCodePtr = g_ByteCode;
	}
	#endif

    // when leave tight interpreter loop to do general system updates,
    // if the user is depressing the top left 10% of screen for more than
    // several seconds, it is an indicator they want to hard-exit the app
	if ( g_iAppIsStandalone==0 )
	{
		static float pointerStartX = 0;
		static float pointerStartY = 0;
		static float pointerStartTime = 0;
		if ( agk::GetPointerPressed() == 1 )
		{
			pointerStartX = agk::GetPointerX();
			pointerStartY = agk::GetPointerY();
			pointerStartTime = agk::Timer();
		}

		// check if we should increase exit timer
		if ( agk::GetPointerState()==1 && agk::GetPointerY()<agk::GetVirtualHeight()/12.5f && pointerStartTime > 0 )
		{
			float fDiffX = agk::GetPointerX() - pointerStartX;
			float fDiffY = agk::GetPointerY() - pointerStartY;
			float fDiffDistance = fDiffX*fDiffX + fDiffY*fDiffY;

			float smallDist = agk::GetRealDeviceWidth()/10.0f;
			
			if ( fDiffDistance > smallDist*smallDist )
			{
				pointerStartTime = 0;
			}
			else
			{
				// timer based exit, 4 seconds
				if ( agk::Timer() - pointerStartTime > 4 )
				{
					// user has held down a while, wants to leave
					g_iAppControlSecretExit = 0;
					AppQuitNow();
				}
			}
		}
		else
		{
			g_iAppControlSecretExit = 0;
		}
	}
}

// Quit app execution
void app::QuitApp ( void )
{
	// instruct program to stop (usually as a result of hitting a runtime error)
	g_iAppControlStage=91;
}

// is app running
bool app::IsRunning ( void )
{
	if ( g_iAppControlStage==0 )
		return true;
	else
		return false;
}

// Close the particulars of the app
void app::CloseApp ( void )
{
	// master reset everything
	agk::SetClearColor ( 0, 0, 0 );
	agk::SetViewOffset ( 0, 0 );
	agk::StopTextInput();
	agk::DeleteAdvert();
	agk::MasterReset();
    agk::Update();

	// free variable buffer
	if ( g_pVarBuffer )
	{
		delete[] g_pVarBuffer;
		g_pVarBuffer = 0;
	}

	// free subroutine stack
	if ( g_pSubroutineStack )
	{
		delete[] g_pSubroutineStack;
		g_pSubroutineStack = 0;
	}
	if ( g_pSubroutineStackEBPStore )
	{
		delete[] g_pSubroutineStackEBPStore;
		g_pSubroutineStackEBPStore = 0;
	}

	// free AGK literal strings
	if ( g_pLiteralString!=NULL )
	{
		for ( DWORD dwI=0; dwI<g_dwLiteralStringMax; dwI++ )
		{
			if ( g_pLiteralString[dwI] )
			{
				delete[] g_pLiteralString[dwI];
				g_pLiteralString[dwI] = NULL;
			}
		}
	}
	g_dwLiteralStringMax = 0;
	if ( g_pLiteralString ) { delete[] g_pLiteralString; g_pLiteralString=0; }

	// free includes list
	if ( g_pIncludesFile )
	{
		for ( DWORD dwI=0; dwI<g_dwIncludesMax; dwI++ ) delete[] g_pIncludesFile[dwI];
		delete[] g_pIncludesFile;
		g_pIncludesFile = NULL;
	}
	if ( g_dwIncludesPos )
	{
		delete[] g_dwIncludesPos;
		g_dwIncludesPos = NULL;
	}
	g_dwIncludesMax = 0;

	// free byte code
	if ( g_ByteCode )
	{
		delete[] g_ByteCode;
		g_ByteCode = 0;
	}
    g_pByteCodePtr = 0;
}

// End app, called once at the end
void app::End ( void )
{
	// if was in scrapper send mode
	if ( g_bScrapperActive==true )
	{
		// close network host
		g_Network1.CloseNetwork();
	}

	// if debugger was active, close that network
	if ( g_bRemoteDebuggingActive==true ) g_DebugNetwork.CloseNetwork();

	// close app if not already done so
	CloseApp();

	// free resources used by interpreter
	if ( g_pAGKBackdrop.pImage ) { delete g_pAGKBackdrop.pImage; g_pAGKBackdrop.pImage=0; }
	if ( g_pAGKBackdrop.pSprite ) { delete g_pAGKBackdrop.pSprite; g_pAGKBackdrop.pSprite=0; }
	if ( g_pAGKBackdropSpinner.pImage ) { delete g_pAGKBackdropSpinner.pImage; g_pAGKBackdropSpinner.pImage=0; }
	if ( g_pAGKBackdropSpinner.pSprite ) { delete g_pAGKBackdropSpinner.pSprite; g_pAGKBackdropSpinner.pSprite=0; }
	if ( g_pAGKBackdropLogo.pImage ) { delete g_pAGKBackdropLogo.pImage; g_pAGKBackdropLogo.pImage=0; }
	if ( g_pAGKBackdropLogo.pSprite ) { delete g_pAGKBackdropLogo.pSprite; g_pAGKBackdropLogo.pSprite=0; }
	if ( g_pAGKBackdropPower.pImage ) { delete g_pAGKBackdropPower.pImage; g_pAGKBackdropPower.pImage=0; }
	if ( g_pAGKBackdropPower.pSprite ) { delete g_pAGKBackdropPower.pSprite; g_pAGKBackdropPower.pSprite=0; }
	if ( g_pText[0] ) { delete g_pText[0]; g_pText[0]=0; }
	if ( g_pText[1] ) { delete g_pText[1]; g_pText[1]=0; }
	if ( g_pText[2] ) { delete g_pText[2]; g_pText[2]=0; }
	if ( g_pText[3] ) { delete g_pText[3]; g_pText[3]=0; }
	if ( g_pVersionNumber ) { delete g_pVersionNumber; g_pVersionNumber=0; }
	if ( g_pArialImage ) { delete g_pArialImage; g_pArialImage=0; }
	if ( g_pAsciiImage ) { delete g_pAsciiImage; g_pAsciiImage=0; }
}
