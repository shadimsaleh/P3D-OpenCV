#include "MeshSystem.h"
#include <Components\Mesh.h>
#include <Components\Transform.h>
#include <Graphics\Camera.h>

GLenum GlType(PrimitiveType type)
{
	switch (type)
	{
	case Triangles:
		return GL_TRIANGLES;
		break;
	case Points:
		return GL_POINTS;
		break;
	case Lines:
		return GL_LINES;
		break;
	}
}

MeshSystem::MeshSystem()
{
}

MeshSystem::~MeshSystem()
{
}

void MeshSystem::OnInitialize(Pool & pool)
{
	group.SetPool(pool);
	group.AllOf<Mesh>();
	group.AllOf<Transform>();
}

void MeshSystem::OnExecute()
{
}

void MeshSystem::OnRender()
{
	for (size_t i = 0; i < group.Size(); i++)
	{
		auto entity = group[i];
		auto mesh = entity->Get<Mesh>();
		auto transform = entity->Get<Transform>();
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		if (Camera::active)
			Camera::active->LookAt(glm::vec3(0, 1, 0));

		glRotatef(transform->rotation.x, 1, 0, 0);
		glRotatef(transform->rotation.y, 0, 1, 0);
		glRotatef(transform->rotation.z, 0, 0, 1);
		glTranslatef(transform->position.x, transform->position.y, transform->position.z);

		glBegin(GlType(mesh->data->GetType()));
		glCallList(mesh->data->GetList());
		glEnd();

		glPopMatrix();
	}
}

void MeshSystem::OnDispose()
{
}