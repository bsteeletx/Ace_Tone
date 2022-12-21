#include "Vector.h"
#include <algorithm>

Vector::Vector(void)
{
	_Start = RFTPoint();
	_Finish = RFTPoint();
}

Vector::Vector(RFTPoint Begin, RFTPoint End)
{
	if (End == RFTPoint())
	{//so you can only give one value if necessary
		_Finish = Begin;
		_Start = RFTPoint();
	}
	else
	{
		_Start = Begin;
		_Finish = End;
	}
}

Vector::~Vector(void)
{
}

Vector& Vector::operator= (const Vector& newVector)
{
	_Start = newVector._Start;
	_Finish = newVector._Finish;

	return *this;
}

/*bool operator== (Vector& First, Vector& Second)
{
	if (First._Start == Second._Start)
	{
		if (First._Finish == Second._Finish)
			return true;
	}

	return false;
}

bool operator!= (Vector& First, Vector& Second)
{
	if (First == Second)
		return false;
	
	return true;
}*/

bool Vector::ContainsPoint(RFTPoint Check)
{
	const float FUZZINESS = 3.0f;
	RFTPoint LeftMostPoint = RFTPoint();
	RFTPoint RightMostPoint = RFTPoint();
	//AGKCore Maths;
	

	if (_Start.GetX() <= _Finish.GetX())
	{
		LeftMostPoint = _Start;
		RightMostPoint = _Finish;
	}
	else
	{
		LeftMostPoint = _Finish;
		RightMostPoint = _Start;
	}
	
	if (Check.GetX() + FUZZINESS < LeftMostPoint.GetX() || RightMostPoint.GetX() < Check.GetX() - FUZZINESS)
		return false;
	else if (Check.GetY() + FUZZINESS < std::min(LeftMostPoint.GetY(), RightMostPoint.GetY()) || std::max(LeftMostPoint.GetY(), RightMostPoint.GetY()) < Check.GetY() - FUZZINESS)
		return false;

	float deltaX = RightMostPoint.GetX() - LeftMostPoint.GetX();
	float deltaY = RightMostPoint.GetY() - LeftMostPoint.GetY();

	if (deltaX == 0 || deltaY == 0)
		return true;
	
	float slope = deltaY / deltaX;
	float offset = LeftMostPoint.GetY() - LeftMostPoint.GetX() * slope;
	float calculatedY = Check.GetX() * slope + offset;

	bool lineContains = Check.GetY() - FUZZINESS <= calculatedY && calculatedY <= Check.GetY() + FUZZINESS;

	return lineContains;
}

RFTPoint Vector::GetDirection(void)
{
	return RFTPoint(GetEndPointX() - GetStartPointX(), GetEndPointY() - GetStartPointY(), GetEndPointZ() - GetStartPointZ());
}

RFTPoint Vector::GetEndPoint(void)
{
	return _Finish;
}

float Vector::GetEndPointX(void)
{
	return _Finish.GetX();
}

float Vector::GetEndPointY(void)
{
	return _Finish.GetY();
}

float Vector::GetEndPointZ(void)
{
	return _Finish.GetZ();
}

RFTPoint Vector::GetMidPoint()
{
	float midX = (_Start.GetX() + _Finish.GetX()) / 2.0f;
	float midY = (_Start.GetY() + _Finish.GetY()) / 2.0f;
	float midZ = (_Start.GetZ() + _Finish.GetZ()) / 2.0f;

	return RFTPoint(midX, midY, midZ);
}

RFTPoint Vector::GetStartPoint(void)
{
	return _Start;
}

float Vector::GetStartPointX(void)
{
	return _Start.GetX();
}

float Vector::GetStartPointY(void)
{
	return _Start.GetY();
}

float Vector::GetStartPointZ(void)
{
	return _Start.GetZ();
}

RFTPoint Vector::GetVelocity(void)
{
	RFTPoint ReturnPoint = RFTPoint();
	ReturnPoint.SetX(GetVelocityInX());
	ReturnPoint.SetY(GetVelocityInY());
	ReturnPoint.SetZ(GetVelocityInZ());

	return ReturnPoint;
}

float Vector::GetVelocityInX(void)
{
	return _Finish.GetX() - _Start.GetX();
}

float Vector::GetVelocityInY(void)
{
	return _Finish.GetY() - _Start.GetY();
}

float Vector::GetVelocityInZ(void)
{
	return _Finish.GetZ() - _Start.GetZ();
}

void Vector::SetStartPoint(RFTPoint Begin)
{
	_Start = Begin;
}

void Vector::SetFinishPoint(RFTPoint End)
{
	_Finish = End;
}

void Vector::SetVectorPoints(RFTPoint Begin, RFTPoint End)
{
	_Start = Begin;
	_Finish = End;
}