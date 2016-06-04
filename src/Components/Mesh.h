#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <vector>
#include <Content\MeshData.h>
#include <memory>

struct Mesh : public IComponent
{
	Mesh(std::shared_ptr<MeshData> data) : data(data) { }

	std::shared_ptr<MeshData> data;
	
	virtual void Reset() override
	{
	}
};