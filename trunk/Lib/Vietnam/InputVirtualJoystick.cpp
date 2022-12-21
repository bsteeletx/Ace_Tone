#include "InputVirtualJoystick.h"
#include "agk.h"

bool VirtualJoystick::_joysticks[4];

VirtualJoystick::VirtualJoystick(RFTPoint Location, float diameter)
{
	_Add(Location, diameter);
}

VirtualJoystick::~VirtualJoystick()
{

}

void VirtualJoystick::Delete()
{

}

bool VirtualJoystick::GetExists()
{
	return (bool)agk::GetVirtualJoystickExists(_joystickID);
}

RFTPoint VirtualJoystick::GetPosition()
{
	return RFTPoint(_GetX(), _GetY());
}

void VirtualJoystick::SetActive(bool isActive)
{
	agk::SetVirtualJoystickActive(_joystickID, (int)isActive);
}

void VirtualJoystick::SetAlpha(unsigned short outer, unsigned short inner)
{
	agk::SetVirtualJoystickAlpha(_joystickID, outer, inner);
}

void VirtualJoystick::SetDeadZone(float value)
{
	agk::SetVirtualJoystickDeadZone(value);
}

void VirtualJoystick::SetImageInner(Image Inner)
{
	agk::SetVirtualJoystickImageInner(_joystickID, Inner.GetID());
}

void VirtualJoystick::SetImageOuter(Image Outer)
{
	agk::SetVirtualJoystickImageOuter(_joystickID, Outer.GetID());
}

void VirtualJoystick::SetPosition(RFTPoint Position)
{
	agk::SetVirtualJoystickPosition(_joystickID, Position.GetX(), Position.GetY());
}

void VirtualJoystick::SetSize(float diameter)
{
	agk::SetVirtualJoystickSize(_joystickID, diameter);
}

void VirtualJoystick::SetVisible(bool isVisible)
{
	agk::SetVirtualJoystickVisible(_joystickID, isVisible);
}

void VirtualJoystick::_Add(RFTPoint Location, float diameter)
{
	_joystickID = _GetJoystickID();

	if (_joystickID != 5)
	{
		_joysticks[_joystickID] = true;

		agk::AddVirtualJoystick(_joystickID, Location.GetX(), Location.GetY(), diameter);
	}
}

unsigned short VirtualJoystick::_GetJoystickID()
{
	for (int i = 0; i < 4; i++)
	{
		if (!_joysticks[i])
			return i;
	}

	return 5;
}

float VirtualJoystick::_GetX()
{
	return agk::GetVirtualJoystickX(_joystickID);
}

float VirtualJoystick::_GetY()
{
	return agk::GetVirtualJoystickY(_joystickID);
}