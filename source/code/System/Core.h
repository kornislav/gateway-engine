#pragma once

#include <Global.h>

class Core
{
public:
	Core();
	~Core();

	bool Init(uint width, uint height);
	void Destroy();

	void Run();

	void SetQuit(bool quit) { _quit = quit; }

private:
	Context* _context;
	Graphics* _graphics;

	bool _quit;

#ifdef WIN32
	MSG _msg;
#endif
};