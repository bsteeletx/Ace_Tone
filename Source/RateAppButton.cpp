#include "RateAppButton.h"


RateAppButton::RateAppButton()
{
}


RateAppButton::~RateAppButton()
{
}

RateAppButton::RateAppButton(RFTPoint Location, float size, unsigned int commonAtlasID)
: Sprite(Color(192, 0, 192))
{
	SetVisible(false);
	SetSize(size);
	SetPosition(Location);
}

/*void RateAppButton::Delete()
{
	
} */

void RateAppButton::Hide()
{
	SetVisible(false);
}

void RateAppButton::Init()
{
	
}

void RateAppButton::Show()
{
	SetVisible(true);
}

void RateAppButton::Update()
{
#if OS != WINDOWS

#endif
}