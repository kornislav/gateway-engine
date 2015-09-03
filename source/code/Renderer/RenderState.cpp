#include "RenderState.h"
#include "Graphics.h"

void RenderState::DrawTriangle(Triangle* triangle)
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}