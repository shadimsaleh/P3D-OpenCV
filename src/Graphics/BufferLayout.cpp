#include "BufferLayout.h"

BufferLayout::BufferLayout() : stride(0), totalElementCount(0)
{
}

BufferLayout::~BufferLayout()
{
}

int BufferLayout::ElementCount()
{
	return totalElementCount;
}

size_t BufferLayout::Size()
{
	return layout.size();
}

GLsizei BufferLayout::Stride()
{
	return stride;
}

const BufferElement & BufferLayout::operator[](size_t i)
{
	return layout[i];
}

void BufferLayout::Push(GLenum type, GLuint size, GLuint count, bool normalized)
{
	layout.push_back({ type, size, count, (GLuint)stride, normalized });
	stride += size * count;
	totalElementCount += count;
}
