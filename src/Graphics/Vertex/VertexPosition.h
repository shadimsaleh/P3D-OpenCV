#pragma once
#include <GL/glew.h>
#include <Graphics\LayoutMapper.h>

struct VertexPosition
{
	VertexPosition(float x, float y, float z) : x(x), y(y), z(z) 
	{
		if (LayoutMapper::GetLayout<VertexPosition>() == nullptr) 
		{
			BufferLayout* layout = new BufferLayout();
			layout->Push<float>(3, false);
			LayoutMapper::SetLayout<VertexPosition>(layout);
		}
	}

	float x;
	float y;
	float z;
};