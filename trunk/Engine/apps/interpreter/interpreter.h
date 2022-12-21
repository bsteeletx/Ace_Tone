#ifndef _H_APP
#define _H_APP

// Handle extra JPG compressor for Windows Player
#ifdef AGKWINDOWS
 #ifdef SCRAPPER
  #include "scrapper\jpegfile.h"
 #endif
 #ifdef SCRAPPERSENDER
  #include "scrapper\jpegfile.h"
 #endif
#endif

#ifdef AGKIOS
#endif

// Link to GDK libraries
#include "agk.h"
#include "AGKCommands.h"

// Auto-generated case code for interpreter switch (from AGK API)
#include "AGKCommandsTable.cpp"
#include "AGKCommandsVersion.h"

// Added for scrapper logic (video streaming to iOS)
#ifdef SCRAPPER
 #import "Texture2D.h"
 #import "cSprite.h"
#endif

// External quit and exit commands
void AppQuitNow ( void );
void AppForceExit ( void );

// Global values for the app
class app
{
	public:

		// main game vars

	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// App
		DWORD g_WindowHandle;
		char g_pCmdLine[512];

		// Data blocks
		DWORD g_dwByteCodeVersion;
		DWORD g_dwByteCodeMax;
		sByteCode* g_ByteCode;
		DWORD g_dwVariableBufferSize;
		char* g_pVarBuffer;
		DWORD g_dwLiteralStringMax;
		char** g_pLiteralString;

		// Includes list data
		DWORD g_dwIncludesMax;
		DWORD* g_dwIncludesPos;
		char** g_pIncludesFile;

		// Subroutine stack
		DWORD g_dwSubroutineStackMax;
		DWORD g_dwSubroutineStackIndex;
		sByteCode** g_pSubroutineStack;
		char** g_pSubroutineStackEBPStore;

		// Function stack (stores vars for user functions)
		DWORD g_dwStackMax;
		char* g_pStack;
		char* g_pStackPtr;
		char* g_pStackPtrEBP;
		char* g_pStackPtrCurrentEBP;
		char* g_pStackEnd;
		char* g_pStackPtrStartOfLocalVarMemBlock;

		// Interpreter vars
		sByteCode* g_pByteCodePtr;
		sByteCode* g_pByteCodeEnd;
		DWORD g_dwCurrentLineNumber;
		DWORD g_dwByteCodeLastLineNumber;
		int g_iCompareValueA;
		int g_iCompareValueB;
		float g_fCompareValueA;
		float g_fCompareValueB;
		char g_pNumToString[256];
		int g_iInstructionCounterStart;
		int g_iInstructionCounter;

		// Flashback system
		DWORD g_dwFBI;
		#define FBMAX 9
		sByteCode* g_pFB[FBMAX];

		// Remote Debugging system
		bool g_bRemoteDebuggingActive;
		bool g_bRemoteDebuggingInProgress;
		int g_iRemoteDebuggingLastLineRemembered;
		int g_iRemoteDebuggingMode;
		int g_iRemoteDebuggingAdvanceToLine;

		// Interpreter graphics view
		cImage* g_pArialImage;
		cImage* g_pAsciiImage;
		struct sAGKHUD
		{
			cImage* pImage;
			cSprite* pSprite; 
		};
		sAGKHUD g_pAGKBackdrop;
		sAGKHUD g_pAGKBackdropSpinner; 
		sAGKHUD g_pAGKBackdropLogo; 
		sAGKHUD g_pAGKBackdropPower; 
		cImage* g_pAGKInterpreterFont;
		AGK::cText* g_pText[4];

		// Interpreter timer
		LONGLONG g_lTimer;
		LONGLONG g_lLastTimer;
		int g_iFrameCount;
		float g_fScreenFPS;

		// Interpreter temp vars
		DWORD g_pi;
		char* g_p[22];
		char* g_pVarPtr;
		char* g_pVarPtrB;
		char* g_pArrayPtr;
		char* g_pArrayPtrB;
		char* g_pStackLocationA;
		char* g_pStackLocationB;

		// Current global states for interpreter
		int g_iMouseClick;
		float g_fMouseX;
		float g_fMouseY;
		float g_fPrintCursorX;
		float g_fPrintCursorY;

		// App Control
		char g_pInterpreterByteCodeFile[512];
		int g_iAppControlStage;
		int g_iAppControlSecretExit;
		int g_iAppIsStandalone;

		// Early initialising variables
		char g_pWindowTitle [ 512 ];
		unsigned int g_dwDeviceWidth;
		unsigned int g_dwDeviceHeight;
		unsigned int g_dwFullScreen;
		unsigned int g_dwResolutionMode;

		// Support functions
		bool LoadApp ( void );
		void QuitApp ( void );
		bool IsRunning ( void );
		void CloseApp ( void );
		void UpdateInputData ( void );
		void WaitingLoop ( void );
		void ScrapperLoop ( void );
		void ScrapperSync ( int iSwapOnly );

		// flashback system - records last 20 line numbers
		void RecordForFlashback ( void ) { g_pFB[g_dwFBI++]=g_pByteCodePtr; if ( g_dwFBI>=FBMAX ) g_dwFBI=0; }
		DWORD GetFlashbackPos ( void ) { return g_dwFBI; }
		sByteCode* GetFlashbackInstruction ( DWORD dwI ) { return g_pFB[dwI]; }

		// Line Number for runtime error
		void RememberLastCommand ( void ) { if ( g_pByteCodePtr ) g_dwByteCodeLastLineNumber = g_pByteCodePtr->dwLineNumber; }
		DWORD GetLastLineNumber ( void ) { return g_dwByteCodeLastLineNumber; }
		void ClearLastCommand ( void ) { g_dwByteCodeLastLineNumber = 0; }

		// Utility functions
		void UpdateInterpreterAspect ( void );
		void InitClean ( void );

		// main app functions
		void Begin( void );
		void Loop( void );
		void End( void );

		// Inline code
		__inline void inl_clearparams(void)
		{
			memset ( g_p, 0, sizeof(g_p) );
		}
		__inline void inl_handleparam_g_11(void)
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
		}
		__inline void inl_handleparam_g_12(void)
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
		}
		__inline void inl_handleparam_g_13(void)
		{
			switch( g_pByteCodePtr->cPType[11+2] )
			{
				case AGKP_VALUE_INTEGER : g_p[11+2] = (char*)&g_pByteCodePtr->iP[11+2]; break;
				case AGKP_VALUE_DWORD : g_p[11+2] = (char*)&g_pByteCodePtr->dwP[11+2]; break;
				case AGKP_VARIABLE_INTEGER : g_p[11+2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->dwP[11+2]); break;
				case AGKP_VARIABLE_DWORD : g_p[11+2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->dwP[11+2]); break;
				case AGKP_OFFSET_INTEGER : g_p[11+2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->iP[11+2]); break;
				case AGKP_OFFSET_DWORD : g_p[11+2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->iP[11+2]); break;
			}
		}
		__inline void inl_handleparam_g_11_index(int ptn)
		{
			// used by PUSHSTACK - so uses g_pStackPtrCurrentEBP not g_pStackPtrEBP
			ptn += 11;
			switch( g_pByteCodePtr->cPType[ptn] )
			{
				case AGKP_VALUE_INTEGER : g_p[ptn] = (char*)&g_pByteCodePtr->iP[ptn]; break;
				case AGKP_VALUE_DWORD : g_p[ptn] = (char*)&g_pByteCodePtr->dwP[ptn]; break;
				case AGKP_VARIABLE_INTEGER : g_p[ptn] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[ptn] + g_pByteCodePtr->dwP[ptn]); break;
				case AGKP_VARIABLE_DWORD : g_p[ptn] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[ptn] + g_pByteCodePtr->dwP[ptn]); break;
				case AGKP_OFFSET_INTEGER : g_p[ptn] = ((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[ptn] + g_pByteCodePtr->iP[ptn]); break;
				case AGKP_OFFSET_DWORD : g_p[ptn] = ((char*)g_pStackPtrCurrentEBP + g_pByteCodePtr->dwPOffset[ptn] + g_pByteCodePtr->iP[ptn]); break;
			}
		}
		__inline void inl_handleparams(void)
		{
			switch ( g_pByteCodePtr->cPType[0] )
			{
				case AGKP_VALUE_INTEGER : g_p[0] = (char*)&g_pByteCodePtr->iP[0]; break;
				case AGKP_VALUE_FLOAT : g_p[0] = (char*)&g_pByteCodePtr->fP[0]; break;
				case AGKP_VALUE_STRING : g_p[0] = (char*)&g_pLiteralString[g_pByteCodePtr->dwP[0]]; break;
				case AGKP_VALUE_DWORD : g_p[0] = (char*)&g_pByteCodePtr->dwP[0]; break;
				case AGKP_VARIABLE_INTEGER : g_p[0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->dwP[0]); break;
				case AGKP_VARIABLE_FLOAT : g_p[0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->dwP[0]); break;
				case AGKP_VARIABLE_STRING : g_p[0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->dwP[0]); break;
				case AGKP_VARIABLE_DWORD : g_p[0] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->dwP[0]); break;
				case AGKP_OFFSET_INTEGER : g_p[0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0]); break;
				case AGKP_OFFSET_FLOAT : g_p[0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0]); break;
				case AGKP_OFFSET_STRING : g_p[0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0]); break;
				case AGKP_OFFSET_DWORD : g_p[0] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[0] + g_pByteCodePtr->iP[0]); break;
				case AGKP_ARRAY_INTEGER : 
				case AGKP_ARRAY_FLOAT : 
				case AGKP_ARRAY_STRING : 
				case AGKP_ARRAY_DWORD : 
				{
					// subscript for array held in shadow params
					switch( g_pByteCodePtr->cPType[11] )
					{
						case AGKP_VALUE_INTEGER : g_p[11] = (char*)&g_pByteCodePtr->iP[11]; break;
						case AGKP_VALUE_DWORD : g_p[11] = (char*)&g_pByteCodePtr->dwP[11]; break;
						case AGKP_VARIABLE_INTEGER : g_p[11] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11] + g_pByteCodePtr->dwP[11]); break;
						case AGKP_VARIABLE_DWORD : g_p[11] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11] + g_pByteCodePtr->dwP[11]); break;
						case AGKP_OFFSET_INTEGER : g_p[11] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11] + g_pByteCodePtr->iP[11]); break;
						case AGKP_OFFSET_DWORD : g_p[11] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11] + g_pByteCodePtr->iP[11]); break;
					}
					g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[0]);
					g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+0])) + g_pByteCodePtr->dwPOffset[0] ));
					g_p[0] = (char*)((int*)g_pArrayPtr);
				}
			}
			if ( g_pByteCodePtr->dwParamCount==1 ) return;
			switch ( g_pByteCodePtr->cPType[1] )
			{
				case AGKP_VALUE_INTEGER : g_p[1] = (char*)&g_pByteCodePtr->iP[1]; break;
				case AGKP_VALUE_FLOAT : g_p[1] = (char*)&g_pByteCodePtr->fP[1]; break;
				case AGKP_VALUE_STRING : g_p[1] = (char*)&g_pLiteralString[g_pByteCodePtr->dwP[1]]; break;
				case AGKP_VALUE_DWORD : g_p[1] = (char*)&g_pByteCodePtr->dwP[1]; break;
				case AGKP_VARIABLE_INTEGER : g_p[1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->dwP[1]); break;
				case AGKP_VARIABLE_FLOAT : g_p[1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->dwP[1]); break;
				case AGKP_VARIABLE_STRING : g_p[1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->dwP[1]); break;
				case AGKP_VARIABLE_DWORD : g_p[1] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->dwP[1]); break;
				case AGKP_OFFSET_INTEGER : g_p[1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1]); break;
				case AGKP_OFFSET_FLOAT : g_p[1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1]); break;
				case AGKP_OFFSET_STRING : g_p[1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1]); break;
				case AGKP_OFFSET_DWORD : g_p[1] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[1] + g_pByteCodePtr->iP[1]); break;
				case AGKP_ARRAY_INTEGER : 
				case AGKP_ARRAY_FLOAT : 
				case AGKP_ARRAY_STRING : 
				case AGKP_ARRAY_DWORD : 
				{
					// subscript for array held in shadow params
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
					g_p[1] = (char*)((DWORD*)g_pArrayPtr);
				}
			}
			if ( g_pByteCodePtr->dwParamCount==2 ) return;
			switch ( g_pByteCodePtr->cPType[2] )
			{
				case AGKP_VALUE_INTEGER : g_p[2] = (char*)&g_pByteCodePtr->iP[2]; break;
				case AGKP_VALUE_FLOAT : g_p[2] = (char*)&g_pByteCodePtr->fP[2]; break;
				case AGKP_VALUE_STRING : g_p[2] = (char*)&g_pLiteralString[g_pByteCodePtr->dwP[2]]; break;
				case AGKP_VALUE_DWORD : g_p[2] = (char*)&g_pByteCodePtr->dwP[2]; break;
				case AGKP_VARIABLE_INTEGER : g_p[2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->dwP[2]); break;
				case AGKP_VARIABLE_FLOAT : g_p[2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->dwP[2]); break;
				case AGKP_VARIABLE_STRING : g_p[2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->dwP[2]); break;
				case AGKP_VARIABLE_DWORD : g_p[2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->dwP[2]); break;
				case AGKP_OFFSET_INTEGER : g_p[2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->iP[2]); break;
				case AGKP_OFFSET_FLOAT : g_p[2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->iP[2]); break;
				case AGKP_OFFSET_STRING : g_p[2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->iP[2]); break;
				case AGKP_OFFSET_DWORD : g_p[2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[2] + g_pByteCodePtr->iP[2]); break;
				case AGKP_ARRAY_INTEGER : 
				case AGKP_ARRAY_FLOAT : 
				case AGKP_ARRAY_STRING : 
				case AGKP_ARRAY_DWORD : 
				{
					// subscript for array held in shadow params
					switch( g_pByteCodePtr->cPType[11+2] )
					{
						case AGKP_VALUE_INTEGER : g_p[11+2] = (char*)&g_pByteCodePtr->iP[11+2]; break;
						case AGKP_VALUE_DWORD : g_p[11+2] = (char*)&g_pByteCodePtr->dwP[11+2]; break;
						case AGKP_VARIABLE_INTEGER : g_p[11+2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->dwP[11+2]); break;
						case AGKP_VARIABLE_DWORD : g_p[11+2] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->dwP[11+2]); break;
						case AGKP_OFFSET_INTEGER : g_p[11+2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->iP[11+2]); break;
						case AGKP_OFFSET_DWORD : g_p[11+2] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+2] + g_pByteCodePtr->iP[11+2]); break;
					}
					g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[2]);
					g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+2])) + g_pByteCodePtr->dwPOffset[2] ));
					g_p[2] = (char*)((DWORD*)g_pArrayPtr);
				}
			}
			if ( g_pByteCodePtr->dwParamCount==3 ) return;
			switch ( g_pByteCodePtr->cPType[3] )
			{
				case AGKP_VALUE_INTEGER : g_p[3] = (char*)&g_pByteCodePtr->iP[3]; break;
				case AGKP_VALUE_FLOAT : g_p[3] = (char*)&g_pByteCodePtr->fP[3]; break;
				case AGKP_VALUE_STRING : g_p[3] = (char*)&g_pLiteralString[g_pByteCodePtr->dwP[3]]; break;
				case AGKP_VALUE_DWORD : g_p[3] = (char*)&g_pByteCodePtr->dwP[3]; break;
				case AGKP_VARIABLE_INTEGER : g_p[3] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->dwP[3]); break;
				case AGKP_VARIABLE_FLOAT : g_p[3] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->dwP[3]); break;
				case AGKP_VARIABLE_STRING : g_p[3] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->dwP[3]); break;
				case AGKP_VARIABLE_DWORD : g_p[3] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->dwP[3]); break;
				case AGKP_OFFSET_INTEGER : g_p[3] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->iP[3]); break;
				case AGKP_OFFSET_FLOAT : g_p[3] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->iP[3]); break;
				case AGKP_OFFSET_STRING : g_p[3] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->iP[3]); break;
				case AGKP_OFFSET_DWORD : g_p[3] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[3] + g_pByteCodePtr->iP[3]); break;
				case AGKP_ARRAY_INTEGER : 
				case AGKP_ARRAY_FLOAT : 
				case AGKP_ARRAY_STRING : 
				case AGKP_ARRAY_DWORD : 
				{
					// subscript for array held in shadow params
					switch( g_pByteCodePtr->cPType[11+3] )
					{
						case AGKP_VALUE_INTEGER : g_p[11+3] = (char*)&g_pByteCodePtr->iP[11+3]; break;
						case AGKP_VALUE_DWORD : g_p[11+3] = (char*)&g_pByteCodePtr->dwP[11+3]; break;
						case AGKP_VARIABLE_INTEGER : g_p[11+3] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+3] + g_pByteCodePtr->dwP[11+3]); break;
						case AGKP_VARIABLE_DWORD : g_p[11+3] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+3] + g_pByteCodePtr->dwP[11+3]); break;
						case AGKP_OFFSET_INTEGER : g_p[11+3] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+3] + g_pByteCodePtr->iP[11+3]); break;
						case AGKP_OFFSET_DWORD : g_p[11+3] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+3] + g_pByteCodePtr->iP[11+3]); break;
					}
					g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[3]);
					g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+3])) + g_pByteCodePtr->dwPOffset[3] ));
					g_p[3] = (char*)((DWORD*)g_pArrayPtr);
				}
			}
			if ( g_pByteCodePtr->dwParamCount==4 ) return;
			switch ( g_pByteCodePtr->cPType[4] )
			{
				case AGKP_VALUE_INTEGER : g_p[4] = (char*)&g_pByteCodePtr->iP[4]; break;
				case AGKP_VALUE_FLOAT : g_p[4] = (char*)&g_pByteCodePtr->fP[4]; break;
				case AGKP_VALUE_STRING : g_p[4] = (char*)&g_pLiteralString[g_pByteCodePtr->dwP[4]]; break;
				case AGKP_VALUE_DWORD : g_p[4] = (char*)&g_pByteCodePtr->dwP[4]; break;
				case AGKP_VARIABLE_INTEGER : g_p[4] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->dwP[4]); break;
				case AGKP_VARIABLE_FLOAT : g_p[4] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->dwP[4]); break;
				case AGKP_VARIABLE_STRING : g_p[4] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->dwP[4]); break;
				case AGKP_VARIABLE_DWORD : g_p[4] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->dwP[4]); break;
				case AGKP_OFFSET_INTEGER : g_p[4] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->iP[4]); break;
				case AGKP_OFFSET_FLOAT : g_p[4] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->iP[4]); break;
				case AGKP_OFFSET_STRING : g_p[4] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->iP[4]); break;
				case AGKP_OFFSET_DWORD : g_p[4] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[4] + g_pByteCodePtr->iP[4]); break;
				case AGKP_ARRAY_INTEGER : 
				case AGKP_ARRAY_FLOAT : 
				case AGKP_ARRAY_STRING : 
				case AGKP_ARRAY_DWORD : 
				{
					// subscript for array held in shadow params
					switch( g_pByteCodePtr->cPType[11+4] )
					{
						case AGKP_VALUE_INTEGER : g_p[11+4] = (char*)&g_pByteCodePtr->iP[11+4]; break;
						case AGKP_VALUE_DWORD : g_p[11+4] = (char*)&g_pByteCodePtr->dwP[11+4]; break;
						case AGKP_VARIABLE_INTEGER : g_p[11+4] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+4] + g_pByteCodePtr->dwP[11+4]); break;
						case AGKP_VARIABLE_DWORD : g_p[11+4] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+4] + g_pByteCodePtr->dwP[11+4]); break;
						case AGKP_OFFSET_INTEGER : g_p[11+4] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+4] + g_pByteCodePtr->iP[11+4]); break;
						case AGKP_OFFSET_DWORD : g_p[11+4] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+4] + g_pByteCodePtr->iP[11+4]); break;
					}
					g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[4]);
					g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+4])) + g_pByteCodePtr->dwPOffset[4] ));
					g_p[4] = (char*)((DWORD*)g_pArrayPtr);
				}
			}
			if ( g_pByteCodePtr->dwParamCount==5 ) return;
			for ( int i=5; i<12; i++ )
			{
				switch ( g_pByteCodePtr->cPType[i] )
				{
					case AGKP_VALUE_INTEGER : g_p[i] = (char*)&g_pByteCodePtr->iP[i]; break;
					case AGKP_VALUE_FLOAT : g_p[i] = (char*)&g_pByteCodePtr->fP[i]; break;
					case AGKP_VALUE_STRING : g_p[i] = (char*)&g_pLiteralString[g_pByteCodePtr->dwP[i]]; break;
					case AGKP_VALUE_DWORD : g_p[i] = (char*)&g_pByteCodePtr->dwP[i]; break;
					case AGKP_VARIABLE_INTEGER : g_p[i] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->dwP[i]); break;
					case AGKP_VARIABLE_FLOAT : g_p[i] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->dwP[i]); break;
					case AGKP_VARIABLE_STRING : g_p[i] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->dwP[i]); break;
					case AGKP_VARIABLE_DWORD : g_p[i] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->dwP[i]); break;
					case AGKP_OFFSET_INTEGER : g_p[i] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->iP[i]); break;
					case AGKP_OFFSET_FLOAT : g_p[i] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->iP[i]); break;
					case AGKP_OFFSET_STRING : g_p[i] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->iP[i]); break;
					case AGKP_OFFSET_DWORD : g_p[i] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[i] + g_pByteCodePtr->iP[i]); break;
					case AGKP_ARRAY_INTEGER : 
					case AGKP_ARRAY_FLOAT : 
					case AGKP_ARRAY_STRING : 
					case AGKP_ARRAY_DWORD : 
					{
						// subscript for array held in shadow params
						switch( g_pByteCodePtr->cPType[11+i] )
						{
							case AGKP_VALUE_INTEGER : g_p[11+i] = (char*)&g_pByteCodePtr->iP[11+i]; break;
							case AGKP_VALUE_DWORD : g_p[11+i] = (char*)&g_pByteCodePtr->dwP[11+i]; break;
							case AGKP_VARIABLE_INTEGER : g_p[11+i] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+i] + g_pByteCodePtr->dwP[11+i]); break;
							case AGKP_VARIABLE_DWORD : g_p[11+i] = ((char*)g_pVarBuffer + g_pByteCodePtr->dwPOffset[11+i] + g_pByteCodePtr->dwP[11+i]); break;
							case AGKP_OFFSET_INTEGER : g_p[11+i] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+i] + g_pByteCodePtr->iP[11+i]); break;
							case AGKP_OFFSET_DWORD : g_p[11+i] = ((char*)g_pStackPtrEBP + g_pByteCodePtr->dwPOffset[11+i] + g_pByteCodePtr->iP[11+i]); break;
						}
						g_pArrayPtr = *(char**)((char*)g_pVarBuffer+g_pByteCodePtr->dwP[i]);
						g_pArrayPtr = (char*)((int*)(g_pArrayPtr+((*((DWORD*)g_pArrayPtr-2))*(*(DWORD*)g_p[11+i])) + g_pByteCodePtr->dwPOffset[i] ));
						g_p[i] = (char*)((DWORD*)g_pArrayPtr);
					}
				}
			}
		}
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif
