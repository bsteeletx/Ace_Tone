#include "LoadingScreen.h"
#include "agk.h"


LoadingScreen::LoadingScreen()
: Sprite()
{
}

LoadingScreen::LoadingScreen(Text FileLocation, Text IconLocation)
: Sprite(FileLocation)
{
	SetSize(100.0f);
	SetDepth(5);

	_LoadingIcon = new LoadingIcon(IconLocation);
	
	_LoadingIcon->SetSize(5.0f);
	_LoadingIcon->SetOffset(RFTPoint(2.5f, 2.5f));
	_LoadingIcon->SetPosition(RFTPoint(25.0f, 75.0f));
	_LoadingIcon->SetDepth(4);
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::Delete()
{
	_LoadingIcon->Delete();
	Sprite::Delete();
}

void LoadingScreen::Hide()
{
	_LoadingIcon->SetVisible(false);
	SetVisible(false);
}

void LoadingScreen::Update()
{
	float x = _LoadingIcon->GetPosition().GetX() + 1.0f;
	float y = _LoadingIcon->GetPosition().GetY();

	_LoadingIcon->SetAngle(_LoadingIcon->GetAngle() + 25.0f);
	_LoadingIcon->SetPosition(RFTPoint(x, y));

	agk::Sync();
}