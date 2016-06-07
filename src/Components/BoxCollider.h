#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>
#include <vector>

struct BoxCollider : public IComponent
{
	BoxCollider(const std::string& tag) : tag(tag) { }
	BoxCollider(const std::string& tag, const glm::vec3& scale) : tag(tag), scale(scale) { }
	BoxCollider(const std::string& tag, const glm::vec3& scale, const glm::vec3& offset) : tag(tag), scale(scale), offset(offset) { }

	std::string tag;
	glm::vec3 offset;
	glm::vec3 scale;

	virtual void Reset() override { }
};