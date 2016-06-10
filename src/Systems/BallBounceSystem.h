#pragma once
#include <Lagswitch\ECS\Pool.h>
#include <Lagswitch\ECS\ISystem.h>
#include <Lagswitch\ECS\Group.h>
#include <Core\Game.h>

class BallBounceSystem : public ISystem
{
public:
	BallBounceSystem();
	~BallBounceSystem();

	static int score;

private:
	virtual void OnInitialize(Pool & pool) override;
	virtual void OnExecute() override;
	virtual void OnRender() override;
	virtual void OnDispose() override;

	Group group;
	Game* game;
	bool debug;
};