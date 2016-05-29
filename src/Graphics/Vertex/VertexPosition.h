#pragma once
#include <GL/glew.h>
#include <Graphics\LayoutMapper.h>
#include <glm\vec3.hpp>

struct VertexPosition
{
	VertexPosition(const glm::vec3& position) : position(position)
	{
		if (LayoutMapper::GetLayout<VertexPosition>() == nullptr) 
		{
			BufferLayout* layout = new BufferLayout();
			layout->Push<float>(3, false);
			LayoutMapper::SetLayout<VertexPosition>(layout);
		}
	}

	glm::vec3 position;
};