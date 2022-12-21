#include "InputPointer.h"
#include "agk.h"

Pointer::Pointer()
: Input()
{

}
Pointer::~Pointer()
{

}

bool Pointer::GetPressed()
{
	return (bool)agk::GetPointerPressed();
}

bool Pointer::GetReleased()
{
	return (bool)agk::GetPointerReleased();
}

bool Pointer::GetState()
{
	return (bool)agk::GetPointerState();
}

RFTPoint Pointer::GetPosition()
{
	return RFTPoint(_GetX(), _GetY());
}

float Pointer::_GetX()
{
	return agk::GetPointerX();
}

float Pointer::_GetY()
{
	return agk::GetPointerY();
}