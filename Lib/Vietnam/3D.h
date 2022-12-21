#pragma once

#include "Point.h"
#include "Quaternion.h"
#include "3DCamera.h"
#include "3DPointLight.h"
#include "3DDirectionalLight.h"
#include "3DShader.h"
#include "3DObject.h"

class ThreeD
{
public:
	ThreeD(unsigned int depth);
	~ThreeD(void);

	std::vector<Camera> Cameras;
	std::vector<PointLight> PointLights;
	std::vector<DirectionalLight> DirectionalLights;
	std::vector<Shader> Shaders;
	std::vector<Object> Objects;
};

