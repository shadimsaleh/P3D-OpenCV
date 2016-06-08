#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>
#include <glm\vec3.hpp>

struct Transform : public IComponent
{
	Transform() : scale(glm::vec3(1)) { }
	Transform(const glm::vec3& position, const glm::vec3& rotation)
		: position(position), rotation(rotation), scale(glm::vec3(1))
	{ }
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: position(position), rotation(rotation), scale(scale)
	{ }

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	virtual void Reset() override
	{
	}
};
