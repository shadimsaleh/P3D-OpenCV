#pragma once
#include <Graphics\LayoutMapper.h>
#include <Graphics\BufferLayout.h>

struct VertexPositionColor
{
	VertexPositionColor(float x, float y, float z, float r, float g, float b, float a) : x(x), y(y), z(z), r(r), g(g), b(b), a(a)
	{
		if (LayoutMapper::GetLayout<VertexPositionColor>() == nullptr)
		{
			BufferLayout* layout = new BufferLayout();
			layout->Push<float>(3, false);
			layout->Push<float>(4, true);
			LayoutMapper::SetLayout<VertexPositionColor>(layout);
		}
	}

	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
};
