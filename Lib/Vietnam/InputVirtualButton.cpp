#include "InputVirtualButton.h"
#include "agk.h"

VirtualButton::VirtualButton(void)
{
	_buttonID = 0;
}

VirtualButton::~VirtualButton(void)
{
	//if (GetExists())
	//	agk::DeleteVirtualButton(_buttonID);
}

VirtualButton::VirtualButton(RFTPoint Location, float size)
{
	_buttonID = GetNextButtonID();
	
	agk::AddVirtualButton(_buttonID, Location.GetX(), Location.GetY(), size);
}

void VirtualButton::Delete()
{
	agk::DeleteVirtualButton(_buttonID);
}

bool VirtualButton::GetExists(void)
{
	if (agk::GetVirtualButtonExists(_buttonID) == 1)
		return true;
	
	return false;
}

bool VirtualButton::GetPressed(void)
{
	if (agk::GetVirtualButtonPressed(_buttonID) == 1)
		return true;

	return false;
}

bool VirtualButton::GetReleased(void)
{
	if (agk::GetVirtualButtonReleased(_buttonID) == 1)
		return true;

	return false;
}

bool VirtualButton::GetState(void)
{
	if (agk::GetVirtualButtonState(_buttonID) == 1)
		return true;

	return false;
}

void VirtualButton::SetActive(bool active)
{
	if (active)
		agk::SetVirtualButtonActive(_buttonID, 1);
	else
		agk::SetVirtualButtonActive(_buttonID, 0);
}

void VirtualButton::SetAlpha(unsigned short alpha)
{
	if (alpha < 256)
		agk::SetVirtualButtonAlpha(_buttonID, alpha);
}

void VirtualButton::SetColor(Color Values)
{
	agk::SetVirtualButtonColor(_buttonID, Values.GetRed(), Values.GetGreen(), Values.GetBlue());
	SetAlpha(Values.GetAlpha());
}

void VirtualButton::SetImageDown(Sprite Object)
{
	agk::SetVirtualButtonImageDown(_buttonID, Object.GetID());
}

void VirtualButton::SetImageUp(Sprite Object)
{
	agk::SetVirtualButtonImageUp(_buttonID, Object.GetID());
}

void VirtualButton::SetPosition(RFTPoint Location)
{
	agk::SetVirtualButtonPosition(_buttonID, Location.GetX(), Location.GetY());
}

void VirtualButton::SetScreenPosition(RFTPoint Location, float size)
{
	if (size >= 0.0f)
		agk::SetButtonScreenPosition(_buttonID, Location.GetX(), Location.GetY(), size);
}

void VirtualButton::SetSize(float size)
{
	if (size >= 0.0f)
		agk::SetVirtualButtonSize(_buttonID, size);
}

void VirtualButton::SetText(Text InnerLabel)
{
	agk::SetVirtualButtonText(_buttonID, InnerLabel.GetCString());
}

void VirtualButton::SetVisible(bool visible)
{
	if (visible)
		agk::SetVirtualButtonVisible(_buttonID, 1);
	else
		agk::SetVirtualButtonVisible(_buttonID, 0);
}