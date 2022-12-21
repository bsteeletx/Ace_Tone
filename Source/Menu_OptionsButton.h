#ifndef _MENU_OPTIONSBUTTON_H_
#define _MENU_OPTIONSBUTTON_H_

//#include "InputVirtualButton.h"
#include "FacebookButton.h"
#include "DifficultyToggle.h"
#include "Slider.h"
#include "GameCenterButton.h"
#include "RateAppButton.h"
#include "ContactUsButton.h"

class OptionsButton : public Sprite
{
public:
	OptionsButton();
	~OptionsButton();
	OptionsButton(unsigned int commonAtlasID);

	void Delete();

	bool GetVisible();

	void HideOptions();

	void Init();

	void ShowOptions();

	void Update(RFTPoint MouseLoc);// = Point(-1.0f, 0.0f));

private:
	unsigned short _difficulty;

	//Sprite *_ButtonImage;
	Sprite *_Background;
	Text *_SettingsText;
	DifficultyToggle *_Difficulty;
	Slider *_VolumeSlider;
	Text *_ConnectText;
#if OS != ANDROID //needs to say IOS at some point
	GameCenterButton *_GameCenterButton;
#endif
	FacebookButton *_FBButton;
	RateAppButton *_RateUs;
	ContactUsButton *_ContactUs;

};

#endif