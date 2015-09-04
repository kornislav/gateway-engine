#include "RenderState.h"
#include "Graphics.h"
#include <Triangle.h>

RenderState::RenderState()
{
}

void RenderState::DrawTriangle(Triangle* triangle)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_VERTEX_ARRAY, triangle->GetVertexBuffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle->GetElementBuffer());
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}