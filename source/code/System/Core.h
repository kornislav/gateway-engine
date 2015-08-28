#pragma once

#include <Global.h>

class Core
{
public:
	Core(int _argc, char** _argv);
	~Core();

	bool Init(uint width, uint height);
	void Destroy();

	void Run();

	void SetQuit(bool quit) { _quit = quit; }

private:
	Context* _context;
	Graphics* _graphics;

	bool _quit;

	int _argc;
	char** _argv;

#ifdef WIN32
	MSG _msg;
#endif
};