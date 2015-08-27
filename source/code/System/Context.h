#pragma once

#include <Global.h>

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

	uint GetWidht() { return _width; }
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