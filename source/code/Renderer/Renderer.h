#pragma once

#include <Global.h>
#include <Triangle.h>
#include <vector>

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
			
		}
	}

	static void Deinitialize() { delete _instance; }

private:
	std::vector<Triangle*> _triangles;

	// Initializes the renderer if it isn't already
	static void Initialize() { if(!_instance) new Renderer; }
	Renderer() { _instance = this; }
	~Renderer() { _instance = nullptr; }
	static Renderer* _instance;
};

Renderer* Renderer::_instance = nullptr;