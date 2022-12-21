#include "RestartButton.h"

RestartButton::RestartButton()
: VirtualButton()
{}

RestartButton::RestartButton(unsigned int commonAtlasID)
: VirtualButton(RFTPoint(55.0f, 75.0f), 10.0f)
{
	_ButtonImage = new Sprite(commonAtlasID, "restart.png");
	_ButtonImage->SetVisible(false);
}

RestartButton::~RestartButton()
{

}

void RestartButton::Init()
{
	SetImageUp(*_ButtonImage);
	SetImageDown(*_ButtonImage);
	//SetVisible(true);
	/*SetSize(10.0f);
	SetPosition(Point(15.0f, 85.0f));*/
}

bool RestartButton::Update()
{
	if (GetPressed())
		return true;

	return false;
}