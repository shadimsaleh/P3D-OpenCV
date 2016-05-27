#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::Load(const std::string & filename)
{
	
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::Unuse()
{
	glUseProgram(0);
}
