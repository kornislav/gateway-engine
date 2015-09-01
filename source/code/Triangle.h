#pragma once

#include <Global.h>

class Triangle
{
public:
	struct Vertex
	{
		float x, y, z, w;
	};

	typedef uint16 Index;

	Triangle();
	~Triangle();

private:
	uint _vertex_buffer;
	uint _element_buffer;
};