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

	uint GetVertexBuffer() { return _vertex_buffer; }
	uint GetElementBuffer() { return _element_buffer; }

private:
	uint _vertex_buffer;
	uint _element_buffer;
};