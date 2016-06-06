#pragma once
#include <glm\glm.hpp>

inline float Lerp(float src, float dst, float t)
{
	return src * t + dst * (1.0f - t);
}

inline glm::vec2 Lerp(const glm::vec2& src, const glm::vec2& dst, float t)
{
	return src * t + dst * (1.0f - t);
}

inline glm::vec3 Lerp(const glm::vec3& src, const glm::vec3& dst, float t)
{
	return src + t * (dst - src);
}

inline glm::vec4 Lerp(const glm::vec4& src, const glm::vec4& dst, float t)
{
	return src * t + dst * (1.0f - t);
}