#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() { glGenBuffers(1, &id); }
VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &id); }

void VertexBuffer::SetLayout(const BufferLayout & bufferLayout)
{
	layout = bufferLayout;
	for (size_t i = 0; i < layout.Size(); i++)
	{
		const BufferElement& element = layout[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized,
			layout.Stride(), (const void*)element.offset);
	}
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}