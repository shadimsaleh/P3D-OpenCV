#include "VertexArray.h"
#include <assert.h>

VertexArray::VertexArray() :
	id(0)
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

VBufferPtr VertexArray::Push()
{
	VBufferPtr buffer = std::make_shared<VertexBuffer>();
	arrayBuffers.push_back(buffer);

	return buffer;
}

VBufferPtr VertexArray::Push(const BufferLayout & layout)
{
	VBufferPtr buffer = Push();
	buffer->Bind();
	buffer->SetLayout(layout);
	buffer->Unbind();
	return buffer;
}

VBufferPtr VertexArray::Peek()
{
	return arrayBuffers.back();
}

IBufferPtr VertexArray::SetIndices(unsigned int count, unsigned int* data, GLenum usage)
{
	indexBuffer = std::make_shared<IndexBuffer>();
	indexBuffer->Bind();
	indexBuffer->SetElements(count, data, usage);

	return indexBuffer;
}

IBufferPtr VertexArray::SetIndices(std::vector<unsigned int>& data, GLenum usage)
{
	return SetIndices(data.size(), &data[0], usage);
}

void VertexArray::Bind()
{
	glBindVertexArray(id);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::Draw(GLenum mode, unsigned int count)
{
	glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
}

int VertexArray::GetIndexCount()
{
	return indexBuffer->GetCount();
}
