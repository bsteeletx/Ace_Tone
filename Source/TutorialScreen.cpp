#include "TutorialScreen.h"

TutorialScreen::TutorialScreen()
: Sprite()
{}

TutorialScreen::TutorialScreen(Text ImageName, unsigned int commonAtlasID)
: Sprite(Color(255, 255, 255))//Sprite(Parent.GetID(), ImageName)
{
	_Title = new Text("", true);

	_Title->SetVisible(false);

	SetVisible(false);
}

TutorialScreen::~TutorialScreen()
{}

void TutorialScreen::Hide()
{
	_Title->SetVisible(false);
	Sprite::SetVisible(false);
}

void TutorialScreen::Init()
{
	Read TextFile = Read("Text/Text_en.txt");
	Text Header = "";
	Text Index = "";

	while (!TextFile.IsEOF())
	{
		Text DataLine = TextFile.Line();
		DataLine.SplitAtDelimeter(&Header, &Index, ':');

		if (Header == "Tutorial")
			_Title->SetString(Index.GetCString());
	}

	SetSize(35.0f);
	SetOffset(RFTPoint(17.5, 17.5));
	SetPositionByOffset(RFTPoint(50.0f, 50.0f));

	_Title->SetColor(Color(0, 0, 0));
	_Title->SetAlignment(CENTER_ALIGNED);
	_Title->SetPosition(RFTPoint(40.0f, 50.0f));
}

void TutorialScreen::Show()
{
	_Title->SetVisible(true);
	Sprite::SetVisible(true);
}