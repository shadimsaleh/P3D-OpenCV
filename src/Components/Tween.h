#pragma once
#include <Core\Math.h>
#include <Lagswitch\ECS\IComponent.h>

enum Interpolation
{
	Linear,
	Spline
};

struct Tween : public IComponent
{
	Tween() : t(0), interval(0), target(glm::vec3(0)) { }
	Tween(float interval) : t(0), interval(interval), target(glm::vec3(0)) { }

	glm::vec3 target;
	float interval;
	float t;

	virtual void Reset() override
	{
		target = glm::vec3(0);
		interval = 0;
	}

	void TweenTo(const glm::vec3 target, float duration)
	{
		this->target = target;
		interval = duration;
	}
};
