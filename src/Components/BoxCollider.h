#pragma once
#include <Lagswitch\ECS\IComponent.h>
#include <glm\vec3.hpp>
#include <vector>
#include <cmath>

struct BoxCollider : public IComponent
{
	BoxCollider(const std::string& tag) : tag(tag), hasCollision(false) { }
	BoxCollider(const std::string& tag, const glm::vec3& min, const glm::vec3& max) : tag(tag), min(min), max(max), hasCollision(false) { }

	std::string tag;
	glm::vec3 min;
	glm::vec3 max;
	bool hasCollision;

	virtual void Reset() override { }

	inline static bool IsColliding(const BoxCollider& a, const BoxCollider& b, const glm::vec3& posA, const glm::vec3& posB, 
		const glm::vec3& scaleA = glm::vec3(1.0f), const glm::vec3& scaleB = glm::vec3(1.0f))
	{
		glm::vec3 minA((a.min + posA) * scaleA);
		glm::vec3 minB((b.min + posB) * scaleB);
		glm::vec3 maxA((a.max + posA) * scaleA);
		glm::vec3 maxB((b.max + posB) * scaleB);

		return (maxA.x > minB.x &&
			minA.x < maxB.x &&
			maxA.y > minB.y &&
			minA.y < maxB.y &&
			maxA.z > minB.z &&
			minA.z < maxB.z);
	}

	inline static glm::vec3 GetLength(const BoxCollider& collider)
	{
		float x = collider.max.x - collider.min.x;
		float y = collider.max.y - collider.min.y;
		float z = collider.max.z - collider.min.z;

		return glm::vec3(x, y, z);
	}
};