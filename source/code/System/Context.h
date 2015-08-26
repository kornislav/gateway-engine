#pragma once

#include <Global.h>

class Context
{
public:
	Context();
	~Context();

	bool InitContext(uint width, uint height);

private:
#ifdef WIN32
	HINSTANCE _instance;
	HWND _window;
#endif
};