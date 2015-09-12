#include "RenderState.h"
#include "Graphics.h"
#include <Triangle.h>

RenderState::RenderState()
{
	
}

void RenderState::DrawTriangle(Triangle* triangle)
{
	glBindBuffer(GL_ARRAY_BUFFER, triangle->GetVertexBuffer());

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(4, GL_FLOAT, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle->GetElementBuffer());
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);

	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}