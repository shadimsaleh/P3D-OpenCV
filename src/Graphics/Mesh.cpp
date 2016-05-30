#include "Mesh.h"

bool Mesh::Load(const std::string & filename)
{
	return true;
}

void Mesh::SetVertexArray(VertexArrayPtr vao)
{
	this->vao = vao;
}

void Mesh::Draw()
{
	Draw(GL_TRIANGLES);
}

void Mesh::Draw(GLenum mode)
{
	vao->Bind();
	vao->Draw(mode, vao->GetIndexCount());
	vao->Unbind();
}

VertexArrayPtr Mesh::GetVertexArray()
{
	return vao;
}
