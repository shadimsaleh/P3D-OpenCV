#pragma once
#include <GL\glew.h>
#include <vector>
#include <Graphics\BufferLayout.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void SetLayout(const BufferLayout& bufferLayout);

	template <typename T>
	void SetData(unsigned int size, T* data, GLenum usage)
	{
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), data, usage);
	}

	void Bind();
	void Unbind();

private:
	GLuint id;
	GLenum type;
	BufferLayout layout;
};