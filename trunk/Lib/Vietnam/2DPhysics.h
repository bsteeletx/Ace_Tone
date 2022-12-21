#ifndef _2DPHYSICS_H_
#define _2DPHYSICS_H_

#include "Point.h"
#include "Sprite.h"
#include "2DPhysicsForce.h"
#include "2DPhysicsContact.h"
#include "2DPhysicsRayCast.h"
#include "2DPhysicsJoint.h"

class Physics2D		 
{
public:
	Physics2D(void);
	~Physics2D(void);

	//////////////////////General & Debug
	void Delete();

	unsigned short GetIslandCount(void);
	float GetSolveTime(void);
		
	void SetCCD(bool isOn = false);
	void SetDebug(bool isDebug);
	void SetGravity(float x, float y);
	void SetMaxPolygonPoints(unsigned short value);
	void SetScale(float value);
	void SetSleeping(bool isSleeping = true);
	void SetThreading(short numOfThreads = -1);
	void SetWalls(bool bottom, bool left, bool right, bool top);
	void SetWallBottom(bool isOn = false);
	void SetWallLeft(bool isOn = false);
	void SetWallRight(bool isOn = false);
	void SetWallTop(bool isOn = false);

	void ToggleDebug();

private:

	////////////////variables and properties
	std::vector<Force> _Forces;
	std::vector<Contact> _Contacts;
	std::vector<RayCast> _RayCasts;
	std::vector<Joint> _Joints;

	bool _debug;
};

#endif