#pragma once

#include <Global.h>

class Context
{
public:
	Context();
	~Context();

	bool Init(uint width, uint height);
	void Destroy();

private:
#ifdef WIN32
	bool CreateConsole();
	void DestroyConsole();

	HINSTANCE _instance;
	HWND _window;
#endif
};