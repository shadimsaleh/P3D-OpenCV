#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

struct BufferElement
{
	GLenum type;
	GLuint size;
	GLuint count;
	GLuint offset;
	GLboolean normalized;
};

class BufferLayout
{
public:
	BufferLayout();
	~BufferLayout();

	template<typename T>
	void Push(GLuint count, bool normalized)
	{
		// Add debug "Invalid type"
	}

	template<>
	void Push<float>(GLuint count, bool normalized) 
	{
		Push(GL_FLOAT, sizeof(float), count, normalized);
	}

	template<>
	void Push<unsigned int>(GLuint count, bool normalized)
	{
		Push(GL_UNSIGNED_INT, sizeof(unsigned int), count, normalized);
	}

	template<>
	void Push<unsigned char>(GLuint count, bool normalized)
	{
		Push(GL_UNSIGNED_BYTE, sizeof(unsigned char), count, normalized);
	}

	int ElementCount();
	size_t Size();
	GLsizei Stride();

	const BufferElement& operator[](size_t i);

private:
	void Push(GLenum type, GLuint size, GLuint count, bool normalized);

	std::vector<BufferElement> layout;
	GLsizei stride;
	int totalElementCount;
};