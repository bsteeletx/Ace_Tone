#include "Rectangle.h"

RectangleBounds::RectangleBounds()
{
	_TopLeft = new RFTPoint();
	_BottomRight = new RFTPoint();
}

RectangleBounds::RectangleBounds(RFTPoint TopLeft, RFTPoint BottomRight)
{
	_TopLeft = new RFTPoint(TopLeft);
	_BottomRight = new RFTPoint(BottomRight);
	_crossesBottom = false;
	_crossesLeft = false;
	_crossesRight = false;
	_crossesTop = false;
}

RectangleBounds::~RectangleBounds()
{}

RectangleBounds& RectangleBounds::operator= (const RectangleBounds& newRectangleBounds)
{
	_TopLeft = newRectangleBounds._TopLeft;
	_BottomRight = newRectangleBounds._BottomRight;
	_crossesBottom = newRectangleBounds._crossesBottom;
	_crossesLeft = newRectangleBounds._crossesLeft;
	_crossesRight = newRectangleBounds._crossesRight;
	_crossesTop = newRectangleBounds._crossesTop;

	return *this;
}

bool RectangleBounds::ContainsPoint(RFTPoint ToCheck)
{
	if (ToCheck.GetX() < GetLeft())
		return false;
	if (ToCheck.GetX() > GetRight())
		return false;
	if (ToCheck.GetY() < GetTop())
		return false;
	if (ToCheck.GetY() > GetBottom())
		return false;

	return true;
}

float RectangleBounds::GetBottom()
{
	return _BottomRight->GetY();
}

RFTPoint RectangleBounds::GetBottomLeft()
{
	return RFTPoint(_TopLeft->GetX(), _BottomRight->GetY());
}

RFTPoint RectangleBounds::GetBottomRight()
{
	return *_BottomRight;
}

bool RectangleBounds::GetCrossedBottom()
{
	return _crossesBottom;
}

bool RectangleBounds::GetCrossedLeft()
{
	return _crossesLeft;
}

bool RectangleBounds::GetCrossedRight()
{
	return _crossesRight;
}

bool RectangleBounds::GetCrossedTop()
{
	return _crossesTop;
}

unsigned short RectangleBounds::GetCrossings()
{
	unsigned short result = 0;

	if (GetCrossedBottom())
		result += 8;
	if (GetCrossedLeft())
		result += 1;
	if (GetCrossedRight())
		result += 4;
	if (GetCrossedTop())
		result += 2;

	return result;
}

float RectangleBounds::GetLeft()
{
	return _TopLeft->GetX();
}

bool RectangleBounds::GetLineIntersects(Vector Line)
{
	if (_GetLineIntersectsLine(Line, Vector(*_TopLeft, GetTopRight())))
		_crossesTop = true;
	if (_GetLineIntersectsLine(Line, Vector(GetTopRight(), *_BottomRight)))
		_crossesRight = true;
	if (_GetLineIntersectsLine(Line, Vector(*_BottomRight, GetBottomLeft())))
		_crossesBottom = true;
	if (_GetLineIntersectsLine(Line, Vector(GetBottomLeft(), *_TopLeft)))
		_crossesLeft = true;
	if (_GetContainsLine(Line))
		return true;

	return _crossesTop || _crossesRight || _crossesLeft || _crossesTop;
}

float RectangleBounds::GetRight()
{
	return _BottomRight->GetX();
}

float RectangleBounds::GetTop()
{
	return _TopLeft->GetY();
}

RFTPoint RectangleBounds::GetTopLeft()
{
	return *_TopLeft;
}

RFTPoint RectangleBounds::GetTopRight()
{
	return RFTPoint(_BottomRight->GetX(), _TopLeft->GetY());
}

bool RectangleBounds::_GetContainsLine(Vector Line)
{
	RFTPoint Start = Line.GetStartPoint();
	RFTPoint End = Line.GetEndPoint();

	if (Start.GetX() < GetLeft())
		return false;
	if (End.GetX() < GetLeft())
		return false;
	if (Start.GetX() > GetRight())
		return false;
	if (End.GetX() > GetRight())
		return false;
	if (Start.GetY() < GetTop())
		return false;
	if (End.GetY() < GetTop())
		return false;
	if (Start.GetY() > GetBottom())
		return false;
	if (End.GetY() > GetBottom())
		return false;

	return true;
}

bool RectangleBounds::_GetLineIntersectsLine(Vector Line1, Vector Line2)
{
	float q = (Line1.GetStartPointY() - Line2.GetStartPointY()) * (Line2.GetEndPointX() - Line2.GetStartPointX()) - (Line1.GetStartPointX() - Line2.GetStartPointX()) * (Line2.GetEndPointY() - Line2.GetStartPointY());
	float d = (Line1.GetEndPointX() - Line1.GetStartPointX()) * (Line2.GetEndPointY() - Line2.GetStartPointY()) - (Line1.GetEndPointY() - Line1.GetStartPointY()) * (Line2.GetEndPointX() - Line2.GetStartPointX());

	//float q = (l1p1.Y - l2p1.Y) * (l2p2.X - l2p1.X) - (l1p1.X - l2p1.X) * (l2p2.Y - l2p1.Y);
	//float d = (l1p2.X - l1p1.X) * (l2p2.Y - l2p1.Y) - (l1p2.Y - l1p1.Y) * (l2p2.X - l2p1.X);

	if (d == 0)
	{
		return false;
	}

	float r = q / d;

	q = (Line1.GetStartPointY() - Line2.GetStartPointY()) * (Line1.GetEndPointX() - Line1.GetStartPointX()) - (Line1.GetStartPointX() - Line2.GetStartPointX()) * (Line1.GetEndPointY() - Line1.GetStartPointY());
	//q = (l1p1.Y - l2p1.Y) * (l1p2.X - l1p1.X) - (l1p1.X - l2p1.X) * (l1p2.Y - l1p1.Y);
	float s = q / d;

	if (r < 0 || r > 1 || s < 0 || s > 1)
	{
		return false;
	}

	return true;
}