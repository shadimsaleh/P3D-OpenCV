#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>
#include <glm\vec3.hpp>

struct Transform : public IComponent
{
	Transform() { }
	Transform(const glm::vec3& position, const glm::vec3& rotation) 
		: position(position), rotation(rotation)
	{ }

	glm::vec3 position;
	glm::vec3 rotation;

	virtual void Reset() override
	{
	}
};
