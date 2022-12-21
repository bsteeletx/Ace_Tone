#ifndef _MENU_H_
#define _MENU_H_

#include "Menu_Tab.h"
#include "Menu_TitleBar.h"
#include "Sprite.h"
#include "InputPointer.h"
#include "Menu_OptionsButton.h"
#include "Advert.h"
#include "Music.h"
#include "LoadingScreen.h"
#include "Sound.h"

class Menu
{
public:
	Menu();
	~Menu();
	Menu(unsigned int commonAtlasID, LoadingScreen ActiveScreen);
	
	void Init(LoadingScreen ActiveScreen);
	float MouseY();
	void Update(int lastLevel, int lastScore);
	short Exit_Status();
	void Cleanup();
	void Scroll(float y);
	void Show();
private:
	TitleBar* _TitleBar;
	Tab* _Tab[5]; //list of tabs
	Tab* _CurrentTab;
	Pointer* _mouse;
	float saved_y;
	float mouse_change;
	Sprite *_Background;
	bool done;
	bool scroll_lock;
	std::vector<unsigned short> _songScores;
	std::vector<int> _songIndex;
	unsigned short song_selected;
	unsigned int _commonAtlasID;
	Sound *_ButtonClick;

	//Songs
	Music *_BackgroundSong;

	///Menu Options
	OptionsButton *_Options;

	//Advert
	Advert *_Ad;

	void _InitData();
	void _RefreshData(int lastLevel, int score);
	void _WriteData();
    bool _WithinValue(float value, float lowRange, float highRange);
};
#endif