#include "RenderState.h"
#include "Graphics.h"
#include <Triangle.h>

void RenderState::DrawTriangle(Triangle* triangle)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle->GetElementBuffer());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}