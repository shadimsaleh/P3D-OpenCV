#pragma once
#include <Lagswitch\ECS\Pool.h>
#include <Lagswitch\ECS\ISystem.h>
#include <Lagswitch\ECS\Group.h>

struct MeshSystem : public ISystem
{
	MeshSystem();
	~MeshSystem();

	virtual void OnInitialize(Pool & pool) override;
	virtual void OnExecute() override;
	virtual void OnRender() override;
	virtual void OnDispose() override;

private:
	Group group;
};