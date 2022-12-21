#pragma once

//#include "Vector.h"
#include "Defines.h"

class RFTPoint
{
public:
	RFTPoint();
	RFTPoint(float loc_x, float loc_y, float loc_z = 0.0f, float lowValue = 0.0f, float hiValue = 100.0f);
	~RFTPoint(void);

	bool operator== (const RFTPoint ComparePoint);
	RFTPoint& operator= (const RFTPoint& NewRFTPoint);
	friend RFTPoint operator+ (const RFTPoint &RFTPoint1, const RFTPoint &RFTPoint2);
	friend RFTPoint operator- (const RFTPoint &RFTPoint1, const RFTPoint &RFTPoint2);

	RFTPoint AddPoint(RFTPoint Additive);
	
	void Floor(void);

	float GetMaxValue(void);
	float GetMinValue(void);
	float GetX(void);
	float GetY(void);
	float GetZ(void);
#if GRIDGAME == 1
	RFTPoint GetGridCoords(void);
	RFTPoint GetNormalCoords(void);
#endif
	RFTPoint Get3DFromScreen(void);
	float Get3DXFromScreen(void);
	float Get3DYFromScreen(void);
    float Get3DZFromScreen(void);
    
    RFTPoint GetScreenFrom3D(void);
    float GetScreenXFrom3D(void);
    float GetScreenYFrom3D(void);

#if GRIDGAME == 1
	void SetCoordsAsGridCoords(void);
#endif
	void SetCoords(float loc_x, float loc_y, float loc_z = 0.0f);
	void SetMaxValue(float value);
	void SetMinValue(float value);
	void SetX(float loc_x);
	void SetY(float loc_y);
	void SetZ(float loc_z);


protected:
	float _x;
	float _y;
	float _z;

private:
	float _maxValue;
	float _minValue;

	float _ContainCoord(float coord);
	void _ContainCoords(float coords[]);
};