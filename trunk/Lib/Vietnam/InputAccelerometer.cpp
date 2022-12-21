#include "InputAccelerometer.h"
#include "agk.h"

//Creates empty Accelerometer object
Accelerometer::Accelerometer(void)
: Input()
{
}

//Destroys Accelerometer object
Accelerometer::~Accelerometer(void)
{
}

//Gets direction of Accelerometer and returns it as a Point Object
RFTPoint Accelerometer::GetDirection()
{
	return RFTPoint(GetDirectionX(), GetDirectionY());
}

//Gets angle of Accelerometer and returns it
float Accelerometer::GetDirectionAngle()
{
	return agk::GetDirectionAngle();
}

//Gets speed of direction and returns it
float Accelerometer::GetDirectionSpeed()
{
	return agk::GetDirectionSpeed();
}

//Gets X value of direction and returns it
float Accelerometer::GetDirectionX()
{
	return agk::GetDirectionX();
}

//Gets Y value of direction and returns it
float Accelerometer::GetDirectionY()
{
	return agk::GetDirectionY();
}