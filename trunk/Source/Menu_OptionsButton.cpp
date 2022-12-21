#include "Menu_OptionsButton.h"
#include "Globals.h"
#include "Sound.h"

OptionsButton::OptionsButton()
{}

OptionsButton::OptionsButton(unsigned int commonAtlasID)
: Sprite(commonAtlasID, "Settings_button.png")
{
	_Background = new Sprite(Color(255, 0, 0, 128));
	_SettingsText = new Text("Settings", true);
	_ConnectText = new Text("Connect", true);
	_Difficulty = new DifficultyToggle(commonAtlasID);
	_VolumeSlider = new Slider(commonAtlasID);
		
#if OS != ANDROID //needs to say IOS at some point
	_GameCenterButton = new GameCenterButton(RFTPoint(25.0f, 77.0f), 15.0f, commonAtlasID);
#endif
	_FBButton = new FacebookButton(RFTPoint(45.0f, 55.0f), 15.0f, commonAtlasID);
	_RateUs = new RateAppButton(RFTPoint(25.0f, 55.0f), 10.0f, commonAtlasID);
	_ContactUs = new ContactUsButton(RFTPoint(45.0f, 77.0f), 10.0f, commonAtlasID);
	
	//Hide what isn't immediately visible
	_Background->SetVisible(false);
	_SettingsText->SetVisible(false);
	_ConnectText->SetVisible(false);
	_FBButton->Hide();
	_ContactUs->Hide();
	_GameCenterButton->Hide();
	_RateUs->Hide();
	_Difficulty->Hide();
	
	SetVisible(false);
}

OptionsButton::~OptionsButton()
{

}

void OptionsButton::Delete()
{
	Sprite::Delete();
	_Background->Delete();
	_SettingsText->Delete();
	_Difficulty->Delete();
	_VolumeSlider->Delete();
	_ConnectText->Delete();
#if OS != ANDROID //needs to say IOS at some point
	_GameCenterButton->Delete();
#endif
	_FBButton->Delete();
	_RateUs->Delete();
	_ContactUs->Delete();
}

bool OptionsButton::GetVisible()
{
	return _Background->GetVisible();
}

void OptionsButton::HideOptions()
{
	_Background->SetVisible(false);
	_SettingsText->SetVisible(false);
	_Difficulty->Hide();
	_VolumeSlider->Hide();
	_ConnectText->SetVisible(false);
#if OS != ANDROID //needs to say IOS at some point
	_GameCenterButton->Hide();
#endif
	_FBButton->Hide();
	_RateUs->Hide();
	_ContactUs->Hide();
}

void OptionsButton::Init()
{
	SetPosition(1.0f, 1.0f);
	SetSize(5.0f);
	SetVisible(true);

	_Background->SetSize(60.0f, 100.0f);
	_Background->SetX(20.0f);
	_Background->SetDepth(8);

	_SettingsText->SetColor(Color(0, 0, 0));
	_SettingsText->SetSize(5.0f);
	_SettingsText->SetPosition(RFTPoint(45.0f, 45.0f));
	
	_ConnectText->SetColor(Color(0, 0, 0));
	_ConnectText->SetSize(5.0f);
	_ConnectText->SetPosition(RFTPoint(45.0f, 30.0f));

	_Difficulty->Init();
	_VolumeSlider->Init();
#if OS != ANDROID //needs to say IOS at some point
	_GameCenterButton->Init();
#endif

	_FBButton->Init();
	_RateUs->Init();
	_ContactUs->Init();
}

void OptionsButton::ShowOptions()
{
	_Background->SetVisible(true);
	_SettingsText->SetVisible(true);
	_Difficulty->Show();
	_VolumeSlider->Show();
	_ConnectText->SetVisible(true);
#if OS != ANDROID //needs to say IOS at some point
	_GameCenterButton->Show();
#endif
	_FBButton->Show();
	_RateUs->Show();
	_ContactUs->Show();
}

void OptionsButton::Update(RFTPoint MouseHitLoc)
{
	Sound Settings;

	if (_Background->GetVisible())
	{
		//update all of the options inside the sprite
		_Difficulty->Update();
		Settings.SetSystemVolume(_VolumeSlider->Update());
#if OS != ANDROID //needs to say IOS at some point
		_GameCenterButton->Update();
#endif
		_FBButton->Update(RFTPoint(-1.0f, 0.0f));
		_RateUs->Update();
		_ContactUs->Update();
	}

	if (MouseHitLoc.GetX() == -1.0f && MouseHitLoc.GetY() == 0.0f)
		return;
	
	if (GetHit(MouseHitLoc))
	{
		if (_Background->GetVisible())
			HideOptions();
		else
			ShowOptions();
	}
}