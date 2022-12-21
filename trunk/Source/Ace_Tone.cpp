// Includes
#include "Ace_Tone.h"
#include "AGKCore.h"

// Namespace
using namespace AGK;

app App;

void app::Begin(void)
{
	AGKCore Setup;
	Setup.SetDisplayAspect(4.0f/3.0f);
	//agk::SetVirtualResolution (1024, 768);
	//agk::SetClearColor( 151,170,204 ); // light blue
	Setup.SetSyncRate(60, 0);
	Setup.SetErrorMode(REPORT_ERROR);
	Setup.SetBorderColor(Color(255, 255, 255));
	Setup.SetOrientationAllowed(0, 0, 1, 1);
	Setup.SetTransitionMode(true);
	Setup.SetClearColor(Color(178, 179, 180));

	_DefualtFontImage = new Image("Text/Cabin Sketch.png");
	Setup.SetDefaultFontImage(_DefualtFontImage->GetID());

	//Load Save Data   --TODO: Check for Save Data

	_levelCount = 0;
	_levelScore = 0; //haven't started yet
	_menuInitialized = false;

	_LoadingScreen = new LoadingScreen("Images/Common/LoadScreen.jpg", "Images/Common/Record.png");
}

void app::Loop (void)
{
	//agk::Print( agk::ScreenFPS() );
	AGKCore TimeCheck;

	agk::Sync();

	switch (_CurrentState)
	{
	case LOADING:
		_CommonAtlas = new Image("Images/Common/Common.png");
		_LoadingScreen->Update();
		_Menu = new Menu(_CommonAtlas->GetID(), *_LoadingScreen); //create menu
		_CurrentState = MENU_INIT;
		break;
	case MENU_INIT:
		if (!_menuInitialized)
		{
			_Menu->Init(*_LoadingScreen);
			_menuInitialized = true;
		}

		if (TimeCheck.GetSeconds() > 5)
		{
			_CurrentState = MENU;
			_LoadingScreen->Hide();
			_LoadingScreen->Delete();
		}
		else
		{
			_LoadingScreen->Update();
		}
		break;
	case MENU:
		_Menu->Update(_levelCount, _levelScore);

		if(_Menu->Exit_Status() != -1)
		{
			_levelCount = _Menu->Exit_Status();
			_Menu->Cleanup();
			_CurrentState = LEVEL_LOAD;
		}

		if (_levelScore == -2)
			_levelScore = 0;
		break;
	case LEVEL_LOAD:
		if (_CurrentLevel != NULL)
			_CurrentLevel->Delete();
		_CurrentLevel = new Level(_levelCount, _CommonAtlas->GetID());
		_CurrentState = LEVEL_INIT;
		break;
	case LEVEL_INIT:
		_CurrentLevel->Init();
		_CurrentState = PLAYING;
		break;
	case PLAYING:
		//call Update Funciton
		_levelScore = _CurrentLevel->Update();

		if (_levelScore != STILLPLAYING)
		{
			_CurrentState = UPDATING;
		}
		break;
	case UPDATING:
		if (_levelScore > 4)
		{
			_Menu->Update(_levelCount, _levelScore - 4);
			_CurrentState = LEVEL_LOAD;
			_levelCount++; //this won't work for everything, but it'll work for testing purposes for now
		}
		else
		{
			_Menu->Update(_levelCount, _levelScore);
			_Menu->Show();
			_CurrentState = MENU;
		}
			
		break;
	}
}


void app::End (void)
{
	_Menu->Update(0, -3);
}
