#include "Shader.h"
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() : id(0)
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string & filename)
{
	GLuint vs = Compile(ReadFromFile(filename + VERTEX_SHADER_EXTENSION), GL_VERTEX_SHADER);
	GLuint fs = Compile(ReadFromFile(filename + FRAGMENT_SHADER_EXTENSION), GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vs);
	glAttachShader(id, fs);
	glLinkProgram(id);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return false;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	GLuint uniformMatricesBlock = glGetUniformBlockIndex(id, "Matrices");
	glUniformBlockBinding(id, uniformMatricesBlock, 0);

	return true;
}

std::string Shader::ReadFromFile(const std::string & filename)
{
	std::ifstream file(filename);

	if (file.fail())
		return "";

	std::string source;
	std::string line;
	while (std::getline(file, line))
	{
		source += line;
		source.push_back('\n');
	}

	return source;
}

GLuint Shader::Compile(const std::string& source, GLenum type)
{
	GLuint shaderId = glCreateShader(type);
	const char* c_str = source.c_str();
	glShaderSource(shaderId, 1, &c_str, NULL);
	glCompileShader(shaderId);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return -1;
	}

	return shaderId;
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::Unuse()
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string & name)
{
	return glGetUniformLocation(id, name.c_str());
}

void Shader::SetUniform(const std::string & name, const glm::mat4 & value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string & name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform(const std::string & name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform(const std::string & name, const glm::vec2 & value)
{
	glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string & name, const glm::vec3 & value)
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string & name, const glm::vec4 & value)
{
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}
