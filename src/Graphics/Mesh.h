#pragma once
#include <Content\IContent.h>
#include <Graphics\VertexArray.h>

class Mesh : public IContent
{
public:
	virtual bool Load(const std::string & filename) override;

	void Draw();
	void Draw(GLenum mode);

	void SetIndices(std::vector<unsigned int>& indices);

	template <typename T>
	void SetVertices(std::vector<T>& vertices)
	{
		SetVertices(vertices, GL_STATIC_DRAW);
	}

	template <typename T>
	void SetVertices(std::vector<T>& vertices, GLenum usage)
	{
		vao.Bind();
		vao.Push(vertices, usage);
		vao.Unbind();
	}

	template <typename T>
	void SetData(std::vector<T>& vertices, std::vector<unsigned int>& indices) 
	{
		vao.Bind();
		vao.Push(vertices, GL_STATIC_DRAW);
		vao.SetIndices(indices, GL_STATIC_DRAW);
		vao.Unbind();
	}

private:
	VertexArray vao;
};
