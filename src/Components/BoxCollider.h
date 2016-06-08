#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>
#include <vector>

struct BoxCollider : public IComponent
{
	BoxCollider(const std::string& tag) : tag(tag), hasCollision(false) { }
	BoxCollider(const std::string& tag, const glm::vec3& min, const glm::vec3& max) : tag(tag), min(min), max(max), hasCollision(false) { }

	std::string tag;
	glm::vec3 min;
	glm::vec3 max;
	bool hasCollision;

	virtual void Reset() override { }

	inline static bool IsColliding(const BoxCollider& a, const BoxCollider& b, const glm::vec3& posA, const glm::vec3& posB)
	{
		glm::vec3 minA(a.min + posA);
		glm::vec3 minB(b.min + posB);
		glm::vec3 maxA(a.max + posA);
		glm::vec3 maxB(b.max + posB);

		if (minA.x > minB.x ||
			minA.y > minB.y ||
			minA.z > minB.z ||
			maxA.x < maxB.x ||
			maxA.y < maxB.y ||
			maxA.z < maxB.z)
		{
			return false;
		}

		return true;
	}
};