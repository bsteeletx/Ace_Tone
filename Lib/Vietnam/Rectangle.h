#pragma once

#include "Point.h"
#include "Vector.h"

class RectangleBounds
{

public:
	RectangleBounds(RFTPoint TopLeft, RFTPoint BottomRight);
	RectangleBounds();
	~RectangleBounds(void);

	RectangleBounds& operator= (const RectangleBounds& newRectangle);

	bool ContainsPoint(RFTPoint ToCheck);

	float GetBottom();
	RFTPoint GetBottomLeft();
	RFTPoint GetBottomRight();
	bool GetCrossedBottom();
	bool GetCrossedLeft();
	bool GetCrossedRight();
	bool GetCrossedTop();
	unsigned short GetCrossings();
	float GetLeft();
	bool GetLineIntersects(Vector Line);
	float GetRight();
	float GetTop();
	RFTPoint GetTopLeft();
	RFTPoint GetTopRight();

private:
	RFTPoint *_TopLeft;
	RFTPoint *_BottomRight;
	bool _crossesBottom;
	bool _crossesLeft;
	bool _crossesRight;
	bool _crossesTop;

	bool _GetContainsLine(Vector Line);
	bool _GetLineIntersectsLine(Vector First, Vector Second);
};