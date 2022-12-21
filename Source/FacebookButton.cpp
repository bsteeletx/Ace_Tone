#include "FacebookButton.h"


FacebookButton::FacebookButton()
: Sprite()
{
}


FacebookButton::~FacebookButton()
{
}

FacebookButton::FacebookButton(RFTPoint Location, float size, unsigned int atlasID)
: Sprite(atlasID, "FB-Logo.png")
{
	SetPosition(Location);
	SetVisible(false);
	SetSize(size);
	
}

/*void FacebookButton::Delete()
{
	
} */

void FacebookButton::Hide()
{
	SetVisible(false);
}

void FacebookButton::Init()
{
	
}

void FacebookButton::Show()
{
	SetVisible(true);
}

void FacebookButton::Update(RFTPoint MouseHitLoc)
{
	if (GetHit(MouseHitLoc))
		_PostOnWall();
}

void FacebookButton::_PostOnWall()
{
	//TODO: FILL IN WHEN IN BETA
#if PLATFORM != PC
	if (_FBCommands->GetLoggedIn())
		_FBCommands->PostOnMyWall("<Link to iTunes>", "<Link to picture of game?>", )
#endif
}