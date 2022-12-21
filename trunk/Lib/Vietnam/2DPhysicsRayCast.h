#pragma once

#include "Defines.h"
#include "3DObject.h"
#include "Text.h"
#include "Vector.h"
#include "Point.h"

class RayCast
{
public:
	RayCast(void);
	~RayCast(void);
	RayCast(Object Casting, Vector Direction, float radius = 0.0f, bool useSlide = false);
	RayCast(Vector Direction, RayCastMode value, int catGroupSpriteID = 0);
	
	void category(unsigned short category);

	float GetFraction(void);
	RFTPoint GetNormal(void);
	float GetNormalX(void);
	float GetNormalY(void);
	/*Point GetObjectBounce(void);
	float GetObjectBounceX(void);
	float GetObjectBounceY(void);
	float GetObjectBounceZ(void);
	float GetObjectDistance(void);
	unsigned int GetObjectHitID(void);
	Point GetObjectPosition(void);
	float GetObjectX(void);
	float GetObjectY(void);
	float GetObjectZ(void);
	Point GetObjectNormal(void);
	float GetObjectNormalX(void);
	float GetObjectNormalY(void);
	float GetObjectNormalZ(void);
	unsigned short GetObjectNumHits(void);
	Point GetObjectSlide(void);
	float GetObjectSlideX(void);
	float GetObjectSlideY(void);
	float GetObjectSlideZ(void);*/
	unsigned int GetSpriteID(void);
	RFTPoint GetPosition(void);
	float GetX(void);
	float GetY(void);
	

private:
	unsigned int _rayCastID;
	bool _anyHits;
};

