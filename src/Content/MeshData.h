#pragma once
#include <Content\IContent.h>
#include <vector>
#include <Graphics\Vertex.h>
#include <GL\glew.h>

enum PrimitiveType
{
	Triangles,
	Points,
	Lines
};

class MeshData : public IContent
{
public:
	virtual bool Load(const std::string & filename) override;
	void SetVertices(std::vector<Vertex>& vertices, PrimitiveType type);
	GLuint GetList();
	PrimitiveType GetType();

private:
	GLuint displayList;
	PrimitiveType type;
};
