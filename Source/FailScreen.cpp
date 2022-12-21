#include "FailScreen.h"
#include "AGKCore.h"

FailScreen::FailScreen()
: Sprite()
{

}

FailScreen::FailScreen(unsigned int commonAtlasID)
: Sprite(Color(255, 255, 255))//CommonAtlas.GetID(), "Fail.png")
{
	_TextDoc = new Read();
	_FailText = new Text("", true);
	_RestartButton = new RestartButton(commonAtlasID);
	_RestartButton->SetVisible(false);
}

FailScreen::~FailScreen()
{

}

void FailScreen::Delete()
{
	_FailText->Delete();
	Sprite::Delete();
	_RestartButton->Delete();
} 

void FailScreen::Init()
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

	while (*_FailText == "")		//since we're only looking to fill this for now
	{
		SettingsText = _TextDoc->Line();
		SettingsText.SplitAtDelimeter(&Header, &Index, ':');

		if (Header == "Fail")
			_FailText = new Text(Index);

		SettingsText.Delete();
	}

	_FailText->SetPosition(RFTPoint(50.0f, 50.0f));
	_FailText->SetSize(10.0f);
	_FailText->SetAlignment(CENTER_ALIGNED);
	_FailText->SetColor(Color(255, 0, 0));
	_FailText->SetVisible(false);

	_RestartButton->Init();

	_TextDoc->Close();
}

void FailScreen::Hide()
{
	Sprite::SetVisible(false);
	_FailText->SetVisible(false);
	_RestartButton->SetVisible(false);
}

void FailScreen::Show()
{
	_FailText->SetVisible(true);
	Sprite::SetVisible(true);
	_RestartButton->SetVisible(true);
}

bool FailScreen::Update()
{
	return _RestartButton->Update();
}