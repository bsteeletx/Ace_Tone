#include "Menu.h"
#include "FileRead.h"
#include "FileWrite.h"
#include "Globals.h"
//#include "Point.h"

Menu::Menu()
{}

Menu::Menu(unsigned int commonAtlasID, LoadingScreen ActiveScreen)
{
	_commonAtlasID = commonAtlasID;
	ActiveScreen.Update();
	_Options = new OptionsButton();
	ActiveScreen.Update();
	_Ad = new Advert();
	ActiveScreen.Update();

	_Background = new Sprite(Color(123, 45, 56));
	ActiveScreen.Update();
	_BackgroundSong = new Music("Audio/Blitzkreig Bop Drum Loop.m4a");
	ActiveScreen.Update();
	
	_TitleBar = new TitleBar();
	ActiveScreen.Update();

	for (int i = 0; i < 5; i++)
	{
		_Tab[i] = new Tab();
		ActiveScreen.Update();
	}

	done = false;
	scroll_lock = true;
	_mouse = new Pointer();
	ActiveScreen.Update();
	saved_y = 0.0f;
	mouse_change = 0.0f;
	song_selected = 1;
	ActiveScreen.Update();

	_ButtonClick = new Sound("Audio/button.wav");
}

Menu::~Menu()
{
}

void Menu::Init(LoadingScreen ActiveScreen)
{
	_InitData();

	_TitleBar = new TitleBar("Images/Common/TitleBar.png");

	_TitleBar->Init();

	ActiveScreen.Update();

	for (int i = 0; i < 5; i++)//create tabs
	{
		_Tab[i] = new Tab(i, 9.5052083f, _commonAtlasID); //had to do hard coded, as artist made it one whole block as opposed to separate pieces
		_Tab[i]->Init();
		ActiveScreen.Update();
	}

	_Options = new OptionsButton(_commonAtlasID);

	ActiveScreen.Update();

	_Background->SetDepth(10); 

	ActiveScreen.Update();

	//Setup
	_CurrentTab = _Tab[0]; //current tab always starts as the first tab
	_CurrentTab->RevealList(); //all tabs initialize as hidden, so show tab1

	ActiveScreen.Update();
	
	//Tab Background
	_Background->SetPosition(_Tab[0]->GetPosition());
	_Background->SetSize(100.0f, _Tab[0]->GetHeight());

	ActiveScreen.Update();

	_Options->Init();

	ActiveScreen.Update();
	
	_Ad = new Advert(1, 2, "ca-app-pub-7829401768374448/7741141477", "", 0.0f, 0.0f, true); //change to false before release
	_Ad->SetVisible(false);

	ActiveScreen.Update();

	//play main menu music
	_BackgroundSong->Play();

	ActiveScreen.Update();
}

float Menu::MouseY()
{
	return _mouse->GetPosition().GetY(); //for convenience
}

void Menu::Update(int lastLevel, int lastScore)
//function that checks everything in real time (loop)
//void Menu::Update()
{
    RFTPoint MousePosition = _mouse->GetPosition();
    bool mousePressed = _mouse->GetPressed();
    bool mouseReleased = _mouse->GetReleased();
    
	if (mousePressed)
		_ButtonClick->Play(50);
    

	if (lastScore > 0)
		_RefreshData(lastLevel, lastScore);
	//else if (lastScore == -2)
		//_InitData();
	else if (lastScore == -3)
		_WriteData();
	//bool value scroll_lock false means you are able to scroll
	//if(!scroll_lock)
	//update options (options update has a check to see if it is visible
	if (mousePressed)
		_Options->Update(MousePosition);
	else
		_Options->Update(RFTPoint(-1.0f, 0.0f));

	if (_Options->GetVisible())
		return;

	_Ad->SetVisible(true);

	if(!scroll_lock) //if scroll lock is false, allow song list to update position based on mouse position
	{
		mouse_change = saved_y - MousePosition.GetY();//measures the change in mouse position and passes the value to everything in list
		Scroll(mouse_change);
	}

	//if mouse is pressed
	if(mousePressed)
	{
		//scroll_lock = true;
		for(int i=0; i<5; i++)//check all tabs for hits
		{
			if(_Tab[i]->GetHit(MousePosition))//checks if pointer is on tab
			{
				if (_Tab[i] != _CurrentTab) //if tab hit is a different tab
				{
					_CurrentTab->HideList();
					_CurrentTab = _Tab[i];
					_CurrentTab->RevealList();
				}
				//else do nothing (clicked on the current tab)
			}
		}
        
		//check if mouse was below the tabs (thus clicking on the list of songs)
		if(MousePosition.GetY() > _CurrentTab->GetHeight() + 16.432292f) //TitleBar Height was returning as 133?!?
		{
			scroll_lock = false; //allow scrolling
			saved_y = MousePosition.GetY(); //save mouse y when pointer first pressed to measure mouse change form this point
		}
	}

	//when mouse is released
	if(mouseReleased)
	{
		//song selected (need to add in detection of menu song mouse hit and pass in that value to exit funciton
		
		scroll_lock = true; //lock scrolling
		_CurrentTab->Stop(); //update all positions

		if (_WithinValue(MousePosition.GetY(), saved_y - 2.5f, saved_y + 2.5f) && _CurrentTab->UpdateMouseClick(MousePosition))
		{
			if (!_CurrentTab->ClickedOnPreview())
			{
				this->done = true;
				song_selected = _CurrentTab->GetSongSelected();
			}
		}
	}
}

bool Menu::_WithinValue(float value, float lowRange, float highRange)
{
    if (value >= lowRange)
    {
        if (value <= highRange)
            return true;
    }
    
    return false;
}

void Menu::Cleanup()
{
	for (int i = 0; i < 5; i++)
		_Tab[i]->Hide();
	_TitleBar->SetVisible(false);
	//_CurrentTab->HideList();//or delete everything?

	_Options->SetVisible(false);
	_Background->SetVisible(false);
	_BackgroundSong->Stop();

	done = false;
}

void Menu::Show()
{
	for (int i = 0; i < 5; i++)
		_Tab[i]->Show();
	_TitleBar->SetVisible(true);
	_CurrentTab->RevealList();

	_Options->SetVisible(true);
	_Background->SetVisible(true);
	_BackgroundSong->Play();

	done = false;
}

short Menu::Exit_Status()
{
	if (done)
		return song_selected;
	else
		return -1;
}

void Menu::Scroll(float y)
{
	//everything updates to their saved position when mouse was clicked - y
	//y changes based on mouse position
	//calls update on everything in list
	_CurrentTab->Update(y);
}

//////////////////
// Read Data File and update values
/////////////////
void Menu::_InitData()
{
	Read FileIn = Read("scores.dat");
	
	if (FileIn.GetID() != 0)
	{
		//Read Scores
		while (!FileIn.IsEOF())
		{
			int songIndex = FileIn.Integer();
			unsigned short value = FileIn.Byte();
			
			_songIndex.push_back(songIndex);
			_songScores.push_back(value);
		}

		for (int i = 0; i < 4; i++)
			_Tab[i]->UpdateScores(_songIndex, _songScores);
	}

	FileIn.Close();

	if (_songScores.size() == 0)
	{
		for (unsigned int i = 0; i < NUMBER_OF_SONGS; i++)
		{
			_songScores.push_back(0);
			_songIndex.push_back(i);
		}
	}
}

void Menu::_RefreshData(int level, int score)
{
	if (_songScores[level] >= score)
		return;
	
	_songScores[level] = score;

	for (int i = 0; i < 4; i++)
		_Tab[i]->UpdateScores(_songIndex, _songScores);
}

/////////////////////
// Write new data file, then call Updata Data to update screen
// Check to make sure score is not below current best first!
//////////////////
void Menu::_WriteData()
{
	Write FileOut = Write("scores.dat");

	for (unsigned int i = 0; i < _songScores.size(); i++)
	{
		FileOut.Integer(_songIndex[i]);
		FileOut.Byte(_songScores[i]);
	}
	
	_songIndex.clear();
	_songScores.clear();

	FileOut.Close();
}