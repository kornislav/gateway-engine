#pragma once

#include <Global.h>
#ifdef WIN32
#define WM_CREATED (WM_USER+1)
#endif

class Context
{
public:
	Context();
	~Context();

	bool Init(uint width, uint height);
	void Destroy();

#ifdef WIN32
	HWND GetWindow() { return _window; }
#endif

	uint GetWidth() { return _width; }
	uint GetHeight() { return _height; }

private:
#ifdef WIN32
	bool CreateConsole();
	void DestroyConsole();

	HINSTANCE _instance;
	HWND _window;
#endif

	uint _width;
	uint _height;
};