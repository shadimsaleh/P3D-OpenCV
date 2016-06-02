#include "Mesh.h"

bool Mesh::Load(const std::string & filename)
{
	return true;
}

void Mesh::Draw()
{
	Draw(GL_TRIANGLES);
}

void Mesh::Draw(GLenum mode)
{
	vao.Bind();
	vao.Draw(mode, vao.GetIndexCount());
	vao.Unbind();
}

void Mesh::SetIndices(std::vector<unsigned int>& indices)
{
	vao.Bind();
	vao.SetIndices(indices, GL_STATIC_DRAW);
	vao.Unbind();
}
