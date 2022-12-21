#include "ContactUsButton.h"


ContactUsButton::ContactUsButton()
{
}


ContactUsButton::~ContactUsButton()
{
}

ContactUsButton::ContactUsButton(RFTPoint Location, float size, unsigned int commonAtlasID)
: Sprite(Color(255, 255, 255))
{
	SetVisible(false);
	SetSize(size);
	SetPosition(Location);
}

/*void ContactUsButton::Delete()
{
	_ButtonImage->Delete();
	VirtualButton::Delete();
}*/

void ContactUsButton::Hide()
{
	SetVisible(false);
}

void ContactUsButton::Init()
{
	/*SetImageDown(*_ButtonImage);
	SetImageUp(*_ButtonImage);*/
}

void ContactUsButton::Show()
{
	SetVisible(true);
}

void ContactUsButton::Update()
{
	//generates pre-populated email from mail client to SC
	//include version info
	//Create a php mailer somehow and send off an email
}