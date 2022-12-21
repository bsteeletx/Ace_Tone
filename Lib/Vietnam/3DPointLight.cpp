#include "3DPointLight.h"
#include "agk.h"

unsigned int PointLight::_lightCounter;

PointLight::PointLight(void)
{
	_lightID = 0;
}

PointLight::PointLight(RFTPoint Location, float radius, Color Value)
{
	if (agk::GetLightPointExists(_lightCounter) == 1)
		_lightID = ++_lightCounter;
	else
		_lightID = 1;

	agk::CreateLightPoint(_lightID, Location.GetX(), Location.GetY(), Location.GetZ(), radius, Value.GetRed(), Value.GetGreen(), Value.GetBlue());
}


PointLight::~PointLight(void)
{
}

PointLight::PointLight(float x, float y, float z, float radius, Color LightColor)
{
	if (agk::GetLightPointExists(_lightCounter) == 1)
		_lightID = ++_lightCounter;
	else
		_lightID = 1;

	agk::CreateLightPoint(_lightID, x, y, z, radius, LightColor.GetRed(), LightColor.GetGreen(), LightColor.GetBlue());
}


void PointLight::Clear(void)
{
	agk::ClearLightPoints();
}

void PointLight::Delete()
{
	agk::DeleteLightPoint(_lightID);
}
	
bool PointLight::GetExists(void)
{
	if (agk::GetLightPointExists(_lightID))
		return true;

	return false;
}

void PointLight::SetColor(Color Value)
{
	agk::SetLightPointColor(_lightID, Value.GetRed(), Value.GetGreen(), Value.GetBlue());
}

void PointLight::SetPosition(RFTPoint Location)
{
	agk::SetLightPointPosition(_lightID, Location.GetX(), Location.GetY(), Location.GetZ());
}
	
void PointLight::SetPosition(float x, float y, float z)
{
	agk::SetLightPointPosition(_lightID, x, y, z);
}
	
void PointLight::SetRadius(float value)
{
	agk::SetLightPointRadius(_lightID, value);
}