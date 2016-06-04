#include "MeshData.h"

bool MeshData::Load(const std::string & filename)
{
	return true;
}

void MeshData::SetVertices(std::vector<Vertex>& vertices, PrimitiveType type)
{
	if (!displayList)
		glDeleteLists(displayList, 1);

	this->type = type;
	displayList = glGenLists(1);

	glNewList(displayList, GL_COMPILE);
	for (size_t w = 0; w < vertices.size(); w++)
	{
		Vertex& v = vertices[w];

		glTexCoord2f(v.uv.x, v.uv.y);
		glNormal3f(v.normal.x, v.normal.y, v.normal.z);
		glColor4f(v.color.r, v.color.g, v.color.b, v.color.a);
		glVertex3f(v.position.x, v.position.y, v.position.z);
	}
	glEndList();
}

GLuint MeshData::GetList()
{
	return displayList;
}

PrimitiveType MeshData::GetType()
{
	return type;
}
