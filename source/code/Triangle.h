#pragma once

#include "Global.h"
#include "Renderer/Graphics.h"

class Triangle
{
public:
	struct Vertex
	{
		float x, y, z, w;
	};

	typedef std::uint16_t Index;

	Triangle();
	~Triangle();

private:
	GLuint _vertex_buffer;
	GLuint _element_buffer;
};