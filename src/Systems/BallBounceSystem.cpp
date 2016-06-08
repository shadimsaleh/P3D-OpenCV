#include "BallBounceSystem.h"
#include <Components\BallController.h>
#include <Components\BoxCollider.h>
#include <Components\Transform.h>
#include <Core\Game.h>
#include <GL\glew.h>

BallBounceSystem::BallBounceSystem()
	: game(Game::Instance()),
	debug(true)
{
}

BallBounceSystem::~BallBounceSystem()
{
}

void BallBounceSystem::OnInitialize(Pool & pool)
{
	group.SetPool(pool);
	group.AllOf<BallController>();
	group.AllOf<BoxCollider>();
	group.AllOf<Transform>();
}

void BallBounceSystem::OnExecute()
{
	for (size_t i = 0; i < group.Size(); i++)
	{
		auto entity = group[i];
		auto ballController = entity->Get<BallController>();
		auto boxCollider = entity->Get<BoxCollider>();
		auto transform = entity->Get<Transform>();

		transform->position += ballController->velocity * (game->GetDeltaTime() / 1000.0f);

		for (size_t j = 0; j < group.Size(); j++)
		{
			auto otherCollider = entity->Get<BoxCollider>();
			if (otherCollider == boxCollider)
				continue;

			auto otherTransform = entity->Get<Transform>();

			bool collision = BoxCollider::IsColliding(*boxCollider, *otherCollider, transform->position, otherTransform->position);
			boxCollider->hasCollision = collision;
			otherCollider->hasCollision = collision;
			if (collision)
			{
				if (otherCollider->tag == "Wall")
				{
					ballController->direction.x = -ballController->direction.x;
					ballController->direction.y = -ballController->direction.y;
				}
			}
		}
	}
}

void BallBounceSystem::OnRender()
{
	if (!debug)
		return;

	for (size_t i = 0; i < group.Size(); i++)
	{
		auto boxCollider = group[i]->Get<BoxCollider>();
		auto transform = group[i]->Get<Transform>();

		glm::vec3 min = boxCollider->min;
		glm::vec3 max = boxCollider->max;
		glm::vec3 pos = transform->position;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glTranslatef(pos.x, pos.y, pos.z);

		glBegin(GL_LINES);

		if (boxCollider->hasCollision) {
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else {
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		}
		
		// min face
		glVertex3f(min.x, min.y, min.z);
		glVertex3f(min.x, max.y, min.z);

		glVertex3f(min.x, max.y, min.z);
		glVertex3f(min.x, max.y, max.z);

		glVertex3f(min.x, max.y, max.z);
		glVertex3f(min.x, min.y, max.z);

		glVertex3f(min.x, min.y, max.z);
		glVertex3f(min.x, min.y, min.z);

		// max face
		glVertex3f(max.x, min.y, min.z);
		glVertex3f(max.x, max.y, min.z);

		glVertex3f(max.x, max.y, min.z);
		glVertex3f(max.x, max.y, max.z);

		glVertex3f(max.x, max.y, max.z);
		glVertex3f(max.x, min.y, max.z);

		glVertex3f(max.x, min.y, max.z);
		glVertex3f(max.x, min.y, min.z);

		// connection
		glVertex3f(min.x, min.y, min.z);
		glVertex3f(max.x, min.y, min.z);

		glVertex3f(min.x, max.y, min.z);
		glVertex3f(max.x, max.y, min.z);

		glVertex3f(min.x, max.y, max.z);
		glVertex3f(max.x, max.y, max.z);

		glVertex3f(min.x, min.y, max.z);
		glVertex3f(max.x, min.y, max.z);
		
		glEnd();
	}
}

void BallBounceSystem::OnDispose()
{
}