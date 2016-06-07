#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>

struct BallController : public IComponent
{
	glm::vec3 velocity;

	virtual void Reset() override { }
};
