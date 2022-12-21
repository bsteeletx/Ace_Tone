#include "LevelBackground.h"

LevelBackground::LevelBackground()
: Sprite()
{}

LevelBackground::LevelBackground(Text ImageLocation)
: Sprite(ImageLocation)
{}

LevelBackground::~LevelBackground()
{}

void LevelBackground::AddTransition(Text ImageLocation)
{
	_Transition = new Sprite(ImageLocation);
	_Transition->SetSize(100.0f);
	_Transition->SetDepth(9998);
	_Transition->SetVisible(true);
}

void LevelBackground::HideTransition()
{
	_Transition->SetVisible(false);
}

void LevelBackground::Init()
{
	SetSize(100.0f);
	SetDepth(9999);

	SetVisible(true);
}

void LevelBackground::ShowTransition()
{
	_Transition->SetVisible(true);
}