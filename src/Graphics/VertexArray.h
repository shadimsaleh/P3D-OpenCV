#pragma once
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <Graphics\BufferLayout.h>
#include <Graphics\Buffers\VertexBuffer.h>
#include <Graphics\Buffers\IndexBuffer.h>
#include <type_traits>

typedef std::shared_ptr<VertexBuffer> VBufferPtr;
typedef std::shared_ptr<IndexBuffer> IBufferPtr;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	VBufferPtr Push();
	VBufferPtr Push(const BufferLayout& layout);
	template <typename T> VBufferPtr Push(const BufferLayout& layout, unsigned int dataCount, const T* data, GLenum usage);
	template <typename T> VBufferPtr Push(unsigned int dataCount, const T* data, GLenum usage);
	template <typename T> VBufferPtr Push(std::vector<T>& data, GLenum usage);
	VBufferPtr Peek();
	IBufferPtr SetIndices(unsigned int count, unsigned int* data, GLenum usage);
	IBufferPtr SetIndices(std::vector<unsigned int>& data, GLenum usage);
	void Bind();
	void Unbind();
	void Draw(GLenum mode, unsigned int count);
	int GetIndexCount();

private:
	GLuint id;
	std::vector<VBufferPtr> arrayBuffers;
	IBufferPtr indexBuffer;
};

template<typename T>
inline VBufferPtr VertexArray::Push(const BufferLayout & layout, unsigned int dataCount, const T * data, GLenum usage)
{
	VBufferPtr buffer = Push();
	buffer->Bind();
	buffer->SetLayout(layout);
	buffer->SetData(dataCount, data, usage);
	buffer->Unbind();

	return buffer;
}

template<typename T>
inline VBufferPtr VertexArray::Push(unsigned int dataCount, const T * data, GLenum usage)
{
	auto bufferLayout = LayoutMapper::GetLayout<T>();

	if (bufferLayout == nullptr)
	{
		return nullptr;
	}

	VBufferPtr buffer = Push();
	buffer->Bind();
	buffer->SetLayout(*bufferLayout);
	buffer->SetData(dataCount, data, usage);
	buffer->Unbind();

	return buffer;
}

template<typename T>
inline VBufferPtr VertexArray::Push(std::vector<T>& data, GLenum usage)
{
	auto bufferLayout = LayoutMapper::GetLayout<T>();

	if (bufferLayout == nullptr)
	{
		return nullptr;
	}

	VBufferPtr buffer = Push();
	buffer->Bind();
	buffer->SetLayout(*bufferLayout);
	buffer->SetData(data.size() * bufferLayout->ElementCount(), data.data(), usage);
	buffer->Unbind();

	return buffer;
}
