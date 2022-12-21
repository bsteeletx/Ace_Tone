#ifndef _H_SLASH_CHORD_
#define _H_SLASH_CHORD_

// Link to GDK libraries
#include "agk.h"
#include "Menu.h"
#include "Level.h"
#include "LoadingScreen.h"

#if OS == IOS
#define AGK_LANDSCAPE
#elif OS == WINDOWS
#define DEVICE_WIDTH 1024
#define DEVICE_HEIGHT 768
#define DEVICE_POS_X 32
#define DEVICE_POS_Y 32
#define FULLSCREEN false
#endif

// Global values for the app
class app
{
	public:

		// constructor
#if OS == IOS
    app() {}
    ~app() {}
#elif OS == WINDOWS
        app() {memset ( this, 0, sizeof(app));}
#endif
    

		// main app functions - mike to experiment with a derived class for this..
		void Begin( void );
		void Loop( void );
		void End( void );

private:
	GameStates _CurrentState;
	Level *_CurrentLevel;
	Image *_DefualtFontImage;

	int _levelCount;
	int _levelScore;
	bool _menuInitialized;
	Menu* _Menu;
	Image *_CommonAtlas;
	LoadingScreen *_LoadingScreen;
};

extern app App;

#endif

#if OS == WINDOWS
#ifdef LoadImage
#undef LoadImage
#endif
#endif