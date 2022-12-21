#include "3DDirectionalLight.h"
#include "agk.h"

unsigned int DirectionalLight::_lightCounter = 0;

DirectionalLight::DirectionalLight(void)
{
	_lightID = 0;
}


DirectionalLight::~DirectionalLight(void)
{
}

DirectionalLight::DirectionalLight(Vector Direction, Color LightColor)
{
	_lightID = ++_lightCounter;
	float dirX = Direction.GetDirection().GetX();
	float dirY = Direction.GetDirection().GetY();
	float dirZ = Direction.GetDirection().GetZ();

	agk::CreateLightDirectional(_lightID, dirX, dirY, dirZ, LightColor.GetRed(), LightColor.GetGreen(), LightColor.GetBlue());
}

void DirectionalLight::Clear(void)
{
	agk::ClearLightDirectionals();
}

void DirectionalLight::Delete()
{
	agk::DeleteLightDirectional(_lightID);
}

bool DirectionalLight::GetExists(void)
{
	if (agk::GetLightDirectionalExists(_lightID)== 1)
		return true;
	
	return false;
}

void DirectionalLight::SetColor(Color Value)
{
	agk::SetLightDirectionalColor(_lightID, Value.GetRed(), Value.GetGreen(), Value.GetBlue());
}

void DirectionalLight::SetDirection(Vector Direction)
{
	float dirX = Direction.GetDirection().GetX();
	float dirY = Direction.GetDirection().GetY();
	float dirZ = Direction.GetDirection().GetZ();

	agk::SetLightDirectionalDirection(_lightID, dirX, dirY, dirZ);
}