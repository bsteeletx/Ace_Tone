#include "InputJoystick.h"
#include "agk.h"

Joystick::Joystick()
: Input()
{

}

Joystick::~Joystick()
{

}

bool Joystick::GetButtonPressed(unsigned short button)
{
	return (bool)agk::GetButtonPressed(button);
}

bool Joystick::GetButtonReleased(unsigned short button)
{
	return (bool)agk::GetButtonReleased(button);
}

bool Joystick::GetButtonState(unsigned short button)
{
	return (bool)agk::GetButtonState(button);
}

RFTPoint Joystick::GetPos()
{
	return RFTPoint(_GetX(), _GetY());
}

void Joystick::SetDeadZone(float deadZoneValue)
{
	agk::SetJoystickDeadZone(deadZoneValue);
}

void Joystick::SetScreenPosition(RFTPoint Position, float size)
{
	_SetScreenPosition(Position.GetX(), Position.GetY(), size);
}

float Joystick::_GetX()
{
	return agk::GetJoystickX();
}

float Joystick::_GetY()
{
	return agk::GetJoystickY();
}

void Joystick::_SetScreenPosition(float x, float y, float size)
{
	agk::SetJoystickScreenPosition(x, y, size);
}