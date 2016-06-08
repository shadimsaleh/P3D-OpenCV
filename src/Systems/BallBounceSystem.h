#pragma once
#include <Lagswitch\ECS\ISystem.h>
#include <Lagswitch\ECS\Group.h>

class BallBounceSystem : public ISystem
{
public:
	BallBounceSystem();
	~BallBounceSystem();

private:
	virtual void OnInitialize(Pool & pool) override;
	virtual void OnExecute() override;
	virtual void OnRender() override;
	virtual void OnDispose() override;

	Group group;
	Game* game;
};