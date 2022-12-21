#include "SettingsButton.h"

SettingsButton::SettingsButton()
: VirtualButton()
{
	_lastUpdate = 0;
}

SettingsButton::SettingsButton(unsigned int commonAtlasID)
: VirtualButton(RFTPoint(93.0f, 94.5f), 3.0f)
{
	_ButtonImage = new Sprite(commonAtlasID, "UIPause.png");
	_ButtonImage->SetVisible(false);
	_lastUpdate = 0;
}

SettingsButton::~SettingsButton()
{

}

unsigned int SettingsButton::GetLastUpdateTime()
{
	return _lastUpdate;
}

void SettingsButton::Init()
{
	SetImageUp(*_ButtonImage);
	SetImageDown(*_ButtonImage);
	SetVisible(true);
	/*SetSize(10.0f);
	SetPosition(Point(15.0f, 85.0f));*/
}

bool SettingsButton::Update(unsigned int currentTime)
{
	_lastUpdate = currentTime;

	if (GetPressed())
		return true;

	return false;
}