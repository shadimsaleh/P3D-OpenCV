#pragma once
#include <Content\IContent.h>
#include <GL\glew.h>

class Shader : public IContent
{
public:
	Shader();
	~Shader();

	virtual void Load(const std::string & filename) override;

	void Use();
	void Unuse();
	
private:
	std::string source;
	GLuint id;
};