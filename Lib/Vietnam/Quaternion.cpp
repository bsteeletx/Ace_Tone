#include "Quaternion.h"


Quaternion::Quaternion(void)
{
	_wRot = _xRot = _yRot = _zRot = 0.0f;
}


Quaternion::~Quaternion(void)
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
{
	_wRot = w;
	_xRot = x;
	_yRot = y;
	_zRot = z;
}

float Quaternion::GetW(void)
{
	return _wRot;
}

float Quaternion::GetX(void)
{
	return _xRot;
}

float Quaternion::GetY(void)
{
	return _yRot;
}

float Quaternion::GetZ(void)
{
	return _zRot;
}

void Quaternion::ResetAllTo(float w, float x, float y, float z)
{
	_wRot = w;
	_xRot = x;
	_yRot = y;
	_zRot = z;
}
	
void Quaternion::SetW(float value)
{
	_wRot = value;
}

void Quaternion::SetX(float value)
{
	_xRot = value;
}

void Quaternion::SetY(float value)
{
	_yRot = value;
}

void Quaternion::SetZ(float value)
{
	_zRot = value;
}