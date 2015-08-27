#pragma once

#include <Global.h>

class Core
{
public:
	Core();
	~Core();

	bool Init(uint width, uint height);
	void Destroy();

private:
	Context* _context;
};