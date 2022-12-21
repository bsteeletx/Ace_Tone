#include "GameCenterButton.h"

GameCenterButton::GameCenterButton()
{
}


GameCenterButton::~GameCenterButton()
{
}

GameCenterButton::GameCenterButton(RFTPoint Location, float size, unsigned int commonAtlasID)
: Sprite(Color(192, 128, 64))
{
	SetVisible(false);
	SetPosition(Location);
	SetSize(size);
}

/*void GameCenterButton::Delete()
{
	Sprite::Delete();
} */

void GameCenterButton::Hide()
{
	SetVisible(false);
}

void GameCenterButton::Init()
{
	
}

void GameCenterButton::Show()
{
	SetVisible(true);
}

void GameCenterButton::Update()
{
#if OS == IOS
	if (GetPressed())
#endif
}