#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>

struct BallController : public IComponent
{
	float velocity;
	glm::vec3 direction;

	virtual void Reset() override { }
};
