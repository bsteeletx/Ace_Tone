#include "3DShader.h"
#include "agk.h"

Shader::Shader(Text VertexFilename, Text PixelFilename)
{
	_shaderID = agk::LoadShader(VertexFilename.GetCString(), PixelFilename.GetCString());
}

Shader::~Shader(void)
{
}

unsigned int Shader::GetID(void)
{
	return _shaderID;
}

void Shader::SetConstantByName(Text Name, float value1, float value2, float value3, float value4)
{
	agk::SetShaderConstantByName(_shaderID, Name.GetCString(), value1, value2, value3, value4);
}