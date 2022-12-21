#pragma once

#include "Point.h"

class Vector
{

public:
	Vector(RFTPoint Begin, RFTPoint End = RFTPoint());
	Vector();
	~Vector(void);

	Vector& operator= (const Vector& newVector);
	/*friend bool operator== (Vector& First, Vector& Second);
	friend bool operator!= (Vector& First, Vector& Second);*/

	bool ContainsPoint(RFTPoint Check);

	RFTPoint GetDirection(void);
	RFTPoint GetEndPoint(void);
	float GetEndPointX(void);
	float GetEndPointY(void);
	float GetEndPointZ(void);
	RFTPoint GetMidPoint(void);
	RFTPoint GetStartPoint(void);
	float GetStartPointX(void);
	float GetStartPointY(void);
	float GetStartPointZ(void);
	RFTPoint GetVelocity(void);
	float GetVelocityInX(void);
	float GetVelocityInY(void);
	float GetVelocityInZ(void);
	
	void SetStartPoint(RFTPoint Begin);
	void SetFinishPoint(RFTPoint End);
	void SetVectorPoints(RFTPoint Begin, RFTPoint End);

private:
	RFTPoint _Start;
	RFTPoint _Finish;
};