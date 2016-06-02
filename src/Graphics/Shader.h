#pragma once
#include <Content\IContent.h>
#include <GL\glew.h>
#include <glm\glm.hpp>

#define VERTEX_SHADER_EXTENSION ".vs"
#define FRAGMENT_SHADER_EXTENSION ".fs"

class Shader : public IContent
{
public:
	Shader();
	~Shader();

	virtual bool Load(const std::string & filename) override;

	void Use();
	void Unuse();
	
	int GetUniformLocation(const std::string& name);
	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, const glm::vec2& value);
	void SetUniform(const std::string& name, const glm::vec3& value);
	void SetUniform(const std::string& name, const glm::vec4& value);
	GLuint GetProgram();
	
private:
	GLuint id;

	std::string ReadFromFile(const std::string& filename);
	GLuint Compile(const std::string& source, GLenum type);
};