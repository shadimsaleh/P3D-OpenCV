#pragma once
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

struct Vertex
{
	Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec3& normal, const glm::vec2& uv)
		: position(position), color(color), normal(normal), uv(uv)
	{
	}

	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
};
