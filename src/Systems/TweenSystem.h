#pragma once
#include <Lagswitch\ECS\Pool.h>
#include <Lagswitch\ECS\ISystem.h>
#include <Lagswitch\ECS\Group.h>

class Game;

class TweenSystem : public ISystem
{
public:
	TweenSystem();
	~TweenSystem();

private:
	virtual void OnInitialize(Pool & pool) override;
	virtual void OnExecute() override;
	virtual void OnRender() override;
	virtual void OnDispose() override;

	Group group;
	Game* game;
};