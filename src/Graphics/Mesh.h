#pragma once
#include <Content\IContent.h>
#include <Graphics\VertexArray.h>

typedef std::shared_ptr<VertexArray> VertexArrayPtr;

class Mesh : public IContent
{
public:
	virtual bool Load(const std::string & filename) override;

	void SetVertexArray(VertexArrayPtr vao);
	void Draw();
	VertexArrayPtr GetVertexArray();

private:
	VertexArrayPtr vao;
};
