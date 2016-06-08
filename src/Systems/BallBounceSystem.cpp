#include "BallBounceSystem.h"
#include <Components\BallController.h>
#include <Components\BoxCollider.h>
#include <Components\Transform.h>
#include <Core\Game.h>

BallBounceSystem::BallBounceSystem()
	: game(Game::Instance())
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


	}
}

void BallBounceSystem::OnRender()
{
}

void BallBounceSystem::OnDispose()
{
}