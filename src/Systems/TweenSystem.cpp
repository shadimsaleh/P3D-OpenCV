#include "TweenSystem.h"
#include <Components\Transform.h>
#include <Components\Tween.h>
#include <Core\Math.h>
#include <Core\Game.h>

TweenSystem::TweenSystem() : game(Game::Instance())
{
}

TweenSystem::~TweenSystem()
{
}

void TweenSystem::OnInitialize(Pool & pool)
{
	group.SetPool(pool);
	group.AllOf<Tween>();
	group.AllOf<Transform>();
}

void TweenSystem::OnExecute()
{
	for (size_t i = 0; i < group.Size(); i++)
	{
		auto entity = group[i];
		auto tween = group[i]->Get<Tween>();
		auto transform = group[i]->Get<Transform>();

		if (tween->target == transform->position) {
			tween->t = 0.0f;
			continue;
		}
			
		tween->t += game->GetDeltaTime() / 1000;
		float x = tween->t / tween->interval;

		transform->position = Lerp(transform->position, tween->target, x);
	}
}

void TweenSystem::OnRender()
{
}

void TweenSystem::OnDispose()
{
}