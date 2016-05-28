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
	vao->Bind();
	vao->Draw(GL_TRIANGLES, vao->GetIndexCount());
	vao->Unbind();
}

VertexArrayPtr Mesh::GetVertexArray()
{
	return vao;
}
