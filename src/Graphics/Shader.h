#pragma once
#include <Content\IContent.h>
#include <GL\glew.h>

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
	
private:
	GLuint id;

	std::string ReadFromFile(const std::string& filename);
	GLuint Compile(const std::string& source, GLenum type);
};