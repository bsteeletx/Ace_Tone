#include "2DPhysics.h"
#include "agk.h"

Physics2D::Physics2D(void)
{
	_debug = false;
}


Physics2D::~Physics2D(void)
{
}

void Physics2D::Delete()
{
	for (int i = 0; i < _Forces.size(); i++)
		_Forces[i].Delete();

	for (int i = 0; i < _Joints.size(); i++)
		_Joints[i].Delete();

	_Forces.clear();
	_Contacts.clear();
	_RayCasts.clear();
	_Joints.clear();
}

unsigned short Physics2D::GetIslandCount(void)
{
	return agk::GetPhysicsIslandCount();
}

float Physics2D::GetSolveTime(void)
{
	return agk::GetPhysicsSolveTime();
}

void Physics2D::SetCCD(bool isOn)
{
	agk::SetPhysicsCCD(isOn);
}

void Physics2D::SetDebug(bool isDebug)
{
	if (isDebug)
		agk::SetPhysicsDebugOn();
	else
		agk::SetPhysicsDebugOff();
}

void Physics2D::SetGravity(float x, float y)
{
	agk::SetPhysicsGravity(x, y);
}

void Physics2D::SetMaxPolygonPoints(unsigned short value)
{
	if (value > 12)
		agk::SetPhysicsMaxPolygonPoints(8);
	else if (value < 2)
		agk::SetPhysicsMaxPolygonPoints(2);
	else
		agk::SetPhysicsMaxPolygonPoints(value);
}

void Physics2D::SetScale(float value)
{
	agk::SetPhysicsScale(value);
}

void Physics2D::SetSleeping(bool isSleeping)
{
	agk::SetPhysicsSleeping((int) isSleeping);
}

void Physics2D::SetThreading(short numOfThreads)
{
	agk::SetPhysicsThreading(numOfThreads);
}

void Physics2D::SetWalls(bool bottom, bool left, bool right, bool top)
{
	SetWallBottom(bottom);
	SetWallLeft(left);
	SetWallRight(right);
	SetWallTop(top);
}

void Physics2D::SetWallBottom(bool isOn)
{
	agk::SetPhysicsWallBottom((int) isOn);
}

void Physics2D::SetWallLeft(bool isOn)
{
	agk::SetPhysicsWallLeft((int) isOn);
}

void Physics2D::SetWallRight(bool isOn)
{
	agk::SetPhysicsWallRight((int) isOn);
}

void Physics2D::SetWallTop(bool isOn)
{
	agk::SetPhysicsWallTop((int) isOn);
}

void Physics2D::ToggleDebug()
{
	_debug = !_debug;
}