#pragma once
#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void SetElements(unsigned int count, unsigned int* data, GLenum usage);
	void Bind();
	void Unbind();
	int GetCount();

private:
	GLuint id;
	int count;
};
