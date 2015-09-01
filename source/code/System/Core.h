#pragma once

#include <Global.h>
#include "Singleton.h"

struct android_app;

class Core : public Singleton<Core>
{
public:
	Core();
	~Core();

#ifdef ANDROID
	bool Init(android_app* state);
#else
	bool Init();
#endif
	void Destroy();

	void Run();

	Graphics* GetGraphics() { return _graphics; }
	Context* GetContext() { return _context; }

	void SetQuit(bool quit) { _quit = quit; }

#ifdef ANDROID
	android_app* GetState() { return _state; }
#endif

private:
	Context* _context;
	Graphics* _graphics;

	bool _quit;

	int _argc;
	char** _argv;

#ifdef WIN32
	MSG _msg;
#elif defined(ANDROID)
	static android_app* _state;
#endif
};