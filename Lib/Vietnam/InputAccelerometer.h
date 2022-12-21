#pragma once

#include "Point.h"
#include "Input.h"

class Accelerometer : Input
{
public:
	Accelerometer();
	~Accelerometer();

	RFTPoint GetDirection();
	float GetDirectionAngle(); 
	float GetDirectionSpeed(); 
	float GetDirectionX(); 
	float GetDirectionY(); 
};