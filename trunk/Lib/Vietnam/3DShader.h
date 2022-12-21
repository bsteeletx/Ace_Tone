#pragma once

#include "Text.h"

class Shader
{
public:
	Shader(Text VertexFilename, Text PixelFilname);
	~Shader(void);

	unsigned int GetID(void);

	void SetConstantByName(Text Name, float value1, float value2, float value3, float value4);

private:
	unsigned int _shaderID;
};

