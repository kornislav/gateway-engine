#include "Triangle.h"
#include <Renderer/Graphics.h>
#include <array>

Triangle::Triangle()
{
	// Create the vertex buffer.
	const std::array<Vertex, 4> vertex_array =
	{
		-1.0f, -1.0f, 0.0f,
		+1.0f, -1.0f, 0.0f,
		-1.0f, +1.0f, 0.0f,
	};

	glGenBuffers( 1, &_vertex_buffer );
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glBufferData( GL_ARRAY_BUFFER, vertex_array.size() * sizeof( decltype( vertex_array )::value_type ), vertex_array.data(), GL_STATIC_DRAW );

	// Create the index buffer.
	const std::array<Index, 6> index_array =
	{
		0, 1, 2
	};

	glGenBuffers( 1, &_element_buffer );
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, index_array.size() * sizeof( decltype( index_array )::value_type ), index_array.data(), GL_STATIC_DRAW );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Triangle::~Triangle()
{
	glDeleteBuffers( 1, &_vertex_buffer );
	glDeleteBuffers( 1, &_element_buffer );
}