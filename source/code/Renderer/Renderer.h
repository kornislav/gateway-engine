#pragma once

#include <Global.h>
#include <Triangle.h>
#include <vector>
#include "RenderState.h"

class Renderer
{
public:
	static void Register(Triangle* triangle)
	{
		Initialize();

		_instance->_triangles.push_back(triangle);
	}

	static void Render()
	{
		Initialize();

		for(auto it: _instance->_triangles)
		{
			_instance->_render_state->DrawTriangle(it);
		}
	}

	static void Deinitialize() { delete _instance; }

private:
	std::vector<Triangle*> _triangles;
	RenderState* _render_state;

	// Initializes the renderer if it isn't already
	static void Initialize() { if(!_instance) new Renderer; }
	Renderer() {
		_instance = this;
		_instance->_render_state = new RenderState();
	}
	~Renderer() { _instance = nullptr; }
	static Renderer* _instance;
};
