#include "SuccessScreen.h"
#include "AGKCore.h"

SuccessScreen::SuccessScreen()
: Sprite()
{
}

SuccessScreen::SuccessScreen(unsigned int commonAtlasID)
: Sprite(Color(255, 255, 255))//this will be changed to use the common atlas eventually//Sprite(CommonAtlas.GetID(), "Success.png")
{
	_TextDoc = new Read();
	_SuccessText = new Text("", true);
	_MainMenuText = new Text("", true);
	_NextSongText = new Text("", true);
	_FBButton = new FacebookButton(RFTPoint(39.0f, 40.0f), 10.0f, commonAtlasID);
	_TwitterCommands = new Twitter();
	_TwitterButton = new Sprite();
	_FacebookLike = new Sprite();
	_MainMenuButton = new Sprite(Color(123, 45, 67));
	_NextSongButton = new Sprite(Color(89, 123, 45));

	_NextSongText->SetVisible(false);

	_commonAtlasID = commonAtlasID;
}

SuccessScreen::~SuccessScreen()
{}

void SuccessScreen::Delete()
{
	_SuccessText->Delete();
	_TwitterButton->Delete();
	Sprite::Delete();
}

void SuccessScreen::Init()
{
	AGKCore Settings;
	Text LocalFileName = "Text/Text_";

	SetVisible(false);
	SetSize(50.0f);
	SetPosition(RFTPoint(25.0f, 25.0f));

	_TwitterButton = new Sprite(_commonAtlasID, "Twitter-Logo.png");
	_TwitterButton->SetPosition(RFTPoint(51.0f, 42.0f));
	_TwitterButton->SetSize(10.0f);

	_FacebookLike = new Sprite(_commonAtlasID, "FB-Like.png");
	_FacebookLike->SetPosition(RFTPoint(45.0f, 56.0f));
	_FacebookLike->SetSize(10.0f);

	_FBButton->Init();

	LocalFileName += Settings.GetDeviceLanguage();
	LocalFileName += ".txt";

	_TextDoc = new Read(LocalFileName);

	if (_TextDoc->GetID() == 0) //no file available
		_TextDoc = new Read("Text/Text_en"); //default to english

	Text SettingsText = Text("");
	Text Header = "";
	Text Index = Text("");

	while (*_NextSongText == "") //only need the one thing
	{
		SettingsText = _TextDoc->Line();
		SettingsText.SplitAtDelimeter(&Header, &Index, ':');

		if (Header == "Success")
			_SuccessText->SetString(Index.GetCString());
		else if (Header == "Main Menu")
			_MainMenuText->SetString(Index.GetCString());
		else if (Header == "Next Song")
			_NextSongText->SetString(Index.GetCString());

		SettingsText.Delete();
	}

	_SuccessText->SetPosition(RFTPoint(50.0f, 30.0f));
	_SuccessText->SetSize(10.0f);
	_SuccessText->SetAlignment(CENTER_ALIGNED);
	_SuccessText->SetColor(Color(0, 255, 0));
	_SuccessText->SetVisible(false);

	_MainMenuButton->SetPosition(RFTPoint(27.5f, 80.0f));
	_MainMenuButton->SetSize(20.0f, 5.0f);
	_MainMenuButton->SetVisible(false);

	_NextSongButton->SetPosition(RFTPoint(52.5f, 80.0f));
	_NextSongButton->SetSize(20.0f, 5.0f);
	_NextSongButton->SetVisible(false);

	_NextSongText->SetSize(5.0f);
	_NextSongText->SetPosition(RFTPoint(70.0f, 80.0f));
	_NextSongText->SetAlignment(RIGHT_ALIGNED);
	_NextSongText->SetColor(Color(0, 0, 0));
	_NextSongText->SetVisible(false);
	_NextSongText->SetDepth(2);

	_MainMenuText->SetSize(5.0f);
	_MainMenuText->SetPosition(RFTPoint(30.0f, 80.0f));
	//_MainMenuText->SetAlignment(CENTER_ALIGNED);
	_MainMenuText->SetColor(Color(255, 255, 255));
	_MainMenuText->SetVisible(false);
	_MainMenuText->SetDepth(2);

	//Show Facebook icon as button
	_FacebookLike->SetVisible(false);
	//show twitter icon as button
	_TwitterButton->SetVisible(false);

	_TextDoc->Close();
}

void SuccessScreen::Hide()
{
	SetVisible(false);
	_SuccessText->SetVisible(false);
	_TwitterButton->SetVisible(false);
	_FacebookLike->SetVisible(false);
	_FBButton->Hide();
	_NextSongText->SetVisible(false);
	_MainMenuText->SetVisible(false);
	_MainMenuButton->SetVisible(false);
	_NextSongButton->SetVisible(false);
}

void SuccessScreen::Show()
{
	SetVisible(true);
	_SuccessText->SetVisible(true);
	_NextSongText->SetVisible(true);
	_MainMenuText->SetVisible(true);
	_TwitterButton->SetVisible(true);
	_FacebookLike->SetVisible(true);
	_FBButton->Show();
	_MainMenuButton->SetVisible(true);
	_NextSongButton->SetVisible(true);
}

int SuccessScreen::Update(RFTPoint MouseHitLoc)
{
	_FBButton->Update(MouseHitLoc);

	if (MouseHitLoc.GetX() == -1.0f && MouseHitLoc.GetY() == 0.0f)
		return -1;

	if (_FacebookLike->GetHit(MouseHitLoc)) //open up html and like?	TODO: FILL IN WHEN IN BETA
		return 1;
	if (_TwitterButton->GetHit(MouseHitLoc)) //post on twitter TODO: SAME AS ABOVE
		return 2;
	if (_NextSongText->GetHitTest(MouseHitLoc) || _NextSongButton->GetHit(MouseHitLoc))
	{
		Hide();
		return 3;
	}
	if (_MainMenuText->GetHitTest(MouseHitLoc) || _MainMenuButton->GetHit(MouseHitLoc))
	{
		Hide();
		return 4;
	}

	return -1;
}