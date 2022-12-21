#include "SettingsScreen.h"
#include "AGKCore.h"

SettingsScreen::SettingsScreen()
: Sprite()
{
	_MuteButton = new MuteButton();
	_RestartButton = new RestartButton();
}

SettingsScreen::SettingsScreen(unsigned int commonAtlasID)
: Sprite(Color (255, 255, 255))//this will be changed to use the common atlas eventually
{
	_TextDoc = new Read();
	_SettingsText = new Text("", true);
	_MuteButton = new MuteButton(commonAtlasID);
	_RestartButton = new RestartButton(commonAtlasID);
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::Delete()
{
	_SettingsText->Delete();
	_MuteButton->Delete();
	_RestartButton->Delete();
	Sprite::Delete();
}

void SettingsScreen::Init()
{
	AGKCore Settings;
	Text LocalFileName = "Text/Text_";

	SetVisible(false);
	SetSize(50.0f);
	SetPosition(RFTPoint(25.0f, 25.0f));

	LocalFileName += Settings.GetDeviceLanguage();
	LocalFileName += ".txt";

	_TextDoc = new Read(LocalFileName);

	if (_TextDoc->GetID() == 0) //no file available
		_TextDoc = new Read("Text/Text_en"); //default to english

	Text SettingsText = Text("", true);
	Text Header = "";
	Text Index = Text("", true);

	while (!_TextDoc->IsEOF())
	{
		SettingsText = _TextDoc->Line();
		SettingsText.SplitAtDelimeter(&Header, &Index, ':');

		if (Header == "Settings")
			_SettingsText = new Text(Index);

		SettingsText.Delete();
	}

	_SettingsText->SetPosition(RFTPoint(50.0f, 50.0f));
	_SettingsText->SetSize(10.0f);
	_SettingsText->SetAlignment(CENTER_ALIGNED);
	_SettingsText->SetColor(Color(0, 0, 0));
	_SettingsText->SetVisible(false);

	_MuteButton->Init();
	_RestartButton->Init();
	_MuteButton->SetVisible(false);
	_RestartButton->SetVisible(false);

	_TextDoc->Close();
}

void SettingsScreen::Hide()
{
	Sprite::SetVisible(false);
	_SettingsText->SetVisible(false);
	_MuteButton->SetVisible(false);
	_RestartButton->SetVisible(false);
}

void SettingsScreen::Show()
{
	_SettingsText->SetVisible(true);
	Sprite::SetVisible(true);
	_MuteButton->SetVisible(true);
	_RestartButton->SetVisible(true);
}

bool SettingsScreen::Update()
{
	_MuteButton->Update();

	if (_RestartButton->Update())
		return true;

	return false;
}