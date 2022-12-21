#include "Point.h"
#include "agk.h"
#include "AGKCore.h"
#include "Defines.h"

RFTPoint::RFTPoint()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_minValue = -100.0f;
	_maxValue = 200.0f;
}

RFTPoint::RFTPoint(float loc_x, float loc_y, float loc_z, float lowValue, float hiValue)
{
	_x = loc_x;
	_y = loc_y;
	_z = loc_z;
	_minValue = lowValue;
	_maxValue = hiValue;
}

RFTPoint::~RFTPoint(void)
{
}

RFTPoint& RFTPoint::operator= (const RFTPoint& NewRFTPoint)
{
	_x = NewRFTPoint._x;
	_y = NewRFTPoint._y;
	_z = NewRFTPoint._z;
	_minValue = NewRFTPoint._minValue;
	_maxValue = NewRFTPoint._maxValue;

	return *this;
}

bool RFTPoint::operator== (RFTPoint CompareRFTPoint)
{
	if (_x != CompareRFTPoint.GetX())
		return false;
	if (_y != CompareRFTPoint.GetY())
		return false;
	if (_z != CompareRFTPoint.GetZ())
		return false;

	return true;
}

RFTPoint operator+ (const RFTPoint &RFTPoint1, const RFTPoint &RFTPoint2)
{
	return RFTPoint(RFTPoint1._x + RFTPoint2._x, RFTPoint1._y + RFTPoint2._y);
}

RFTPoint operator- (const RFTPoint &RFTPoint1, const RFTPoint &RFTPoint2)
{
	return RFTPoint(RFTPoint1._x - RFTPoint2._x, RFTPoint1._y - RFTPoint2._y);
}

RFTPoint RFTPoint::AddPoint(RFTPoint Additive)
{
	RFTPoint Start = *this;

	Start._x += Additive._x;
	Start._y += Additive._y;
	Start._z += Additive._z;

	*this = Start;

	return Start;
}

void RFTPoint::Floor(void)
{
    AGKCore Maths;
	_x = (float) Maths.Floor(_x);
	_y = (float) Maths.Floor(_x);
	_z = (float) Maths.Floor(_x);
}

RFTPoint RFTPoint::Get3DFromScreen(void)
{
	return RFTPoint(Get3DXFromScreen(), Get3DYFromScreen(), Get3DZFromScreen());
}

float RFTPoint::Get3DXFromScreen(void)
{
	return agk::Get3DVectorXFromScreen(_x, _y);
}

float RFTPoint::Get3DYFromScreen(void)
{
	return agk::Get3DVectorYFromScreen(_x, _y);
}

float RFTPoint::Get3DZFromScreen(void)
{
	return agk::Get3DVectorZFromScreen(_x, _y);
}

float RFTPoint::GetMaxValue(void)
{
	return _maxValue;
}

float RFTPoint::GetMinValue(void)
{
	return _minValue;
}

RFTPoint RFTPoint::GetScreenFrom3D(void)
{
	return RFTPoint(GetScreenXFrom3D(), GetScreenYFrom3D());
}

float RFTPoint::GetScreenXFrom3D(void)
{
    AGKCore Converter;
    
	return agk::GetScreenXFrom3D(_x, _y, _z);
}

float RFTPoint::GetScreenYFrom3D(void)
{
	return agk::GetScreenYFrom3D(_x, _y, _z);
}

float RFTPoint::GetX(void)
{
	return _x;
}

float RFTPoint::GetY(void)
{
	return _y;
}

float RFTPoint::GetZ(void)
{
	return _z;
}

#if GRIDGAME == 1
RFTPoint RFTPoint::GetGridCoords(void)
{
	float xLoc = 0.0f;
	float yLoc = 0.0f;

	if (y < YBEG - SPOT_BORDER_Y - 1.0f)
	{
		xLoc = (_x - XBEG_MENU + MENU_BORDER)/(SPOT_WIDTH);
		yLoc = -1.0f;

		if (xLoc > XMAX)
			xLoc = XMAX;
	}
	else
	{
		xLoc = (_x - XBEG - SPOT_BORDER_X)/(SPOT_WIDTH);
		yLoc = (_y - YBEG - SPOT_BORDER_Y)/SPOT_HEIGHT;
	}

	return RFTPoint(agk::Round(xLoc), agk::Round(yLoc));
}

RFTPoint RFTPoint::GetNormalCoords(void)
{
	float xLoc = _x;
	float yLoc = _y;
	
	xLoc = xLoc*(SPOT_WIDTH) + XBEG + SPOT_BORDER_X;
	yLoc = yLoc*(SPOT_HEIGHT) + YBEG + SPOT_BORDER_Y;

	if (y >= 0)
	{
		if (xLoc < XBEG + SPOT_BORDER_X)
			xLoc = XBEG + SPOT_BORDER_X;
		if (yLoc < YBEG - SPOT_HEIGHT + SPOT_BORDER_Y)
			yLoc = YBEG - SPOT_HEIGHT + SPOT_BORDER_Y;
		if (xLoc > XMAX*(SPOT_WIDTH) + XBEG + SPOT_BORDER_X)
			xLoc = XMAX*(SPOT_WIDTH) + XBEG + SPOT_BORDER_X;
		if (yLoc > YMAX*(SPOT_HEIGHT) + YBEG + SPOT_BORDER_Y)
			yLoc = YMAX*(SPOT_HEIGHT) + YBEG + SPOT_BORDER_Y;

		/*if (y == 0)
		{
			yLoc -= 1.0f;
			xLoc -= 0.1f;
		}*/
	}
	else
	{
		yLoc = MENU_Y;
		
		if (xLoc < XBEG_MENU)
			xLoc = XBEG_MENU;
		else if (xLoc > XMAX*(SPOT_WIDTH + MENU_BORDER) + XBEG_MENU)
			xLoc = XMAX*(SPOT_WIDTH + MENU_BORDER) + XBEG_MENU;
		else
			xLoc = _x*(SPOT_WIDTH) + XBEG_MENU;
	}
		
	
	return RFTPoint(xLoc, yLoc);
}

void RFTPoint::SetCoordsAsGridCoords(void)
{
	/*x = (int) ((x - XBEG)/(SPOT_WIDTH + SPOT_BORDER));
	y = ((y - YBEG)/(SPOT_HEIGHT + SPOT_BORDER));

	if (y < 0.0f)
		y = -1.0f;
	else
		y = (int) y;*/

	*this = RFTPoint(GetGridCoords());
}
#endif

void RFTPoint::SetCoords(float loc_x, float loc_y, float loc_z)
{
	float values[3] = {loc_x, loc_y, loc_z};
	
	_ContainCoords(values);

	_x = values[0];
	_y = values[1];
	_z = values[2];
}

void RFTPoint::SetX(float loc_x)
{
	_x = _ContainCoord(loc_x);
}

void RFTPoint::SetY(float loc_y)
{
	_y = _ContainCoord(loc_y);
}

void RFTPoint::SetZ(float loc_z)
{
	_z = _ContainCoord(loc_z);
}

float RFTPoint::_ContainCoord(float coord)
{
	if (coord < _minValue)
		return _minValue;
	else if (coord > _maxValue)
		return _maxValue;
	else
		return coord;
}

void RFTPoint::_ContainCoords(float coords[])
{
	for (int i = 0; i < 3; i++)
		coords[i] = _ContainCoord(coords[i]);
}