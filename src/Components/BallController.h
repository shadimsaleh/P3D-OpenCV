#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>

struct BallController : public IComponent
{
	BallController(const glm::vec3& direction, float velocity) : direction(direction), velocity(velocity) {}

	float velocity;
	glm::vec3 direction;

	virtual void Reset() override { }
};
