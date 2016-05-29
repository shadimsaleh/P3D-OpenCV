#pragma once
#include <Graphics\LayoutMapper.h>
#include <Graphics\BufferLayout.h>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

struct VertexPositionColor
{
	VertexPositionColor(const glm::vec3& pos, const glm::vec4& color) : position(pos), color(color)
	{
		if (LayoutMapper::GetLayout<VertexPositionColor>() == nullptr)
		{
			BufferLayout* layout = new BufferLayout();
			layout->Push<float>(3, false);
			layout->Push<float>(4, true);
			LayoutMapper::SetLayout<VertexPositionColor>(layout);
		}
	}

	glm::vec3 position;
	glm::vec4 color;
};
