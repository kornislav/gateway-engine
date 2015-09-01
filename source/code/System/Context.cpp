#include "Context.h"

#ifdef WIN32
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#elif defined(ANDROID)
#include <android/android_native_app_glue.h>
#endif
#include "Core.h"

#ifdef WIN32
LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    switch(message)
    {
	case WM_CREATED:
		Core::GetInstance().OnWindowCreate();
		break;
    case WM_DESTROY:
		PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(window, message, w_param, l_param);
    }
    return 0;
}
#elif defined(ANDROID)
static void android_handle_cmd(struct android_app* app, int cmd)
{
	switch(cmd)
	{
	case APP_CMD_INIT_WINDOW:
	{
		Core::GetInstance().OnWindowCreate();
	}
	break;

	case APP_CMD_DESTROY:
	{
	}
	break;

	case APP_CMD_TERM_WINDOW:
	{
	}
	break;

	case APP_CMD_RESUME:
	{
	}
	break;

	case APP_CMD_PAUSE:
	{
	}
	break;
	}
}
#endif

Context::Context()
	: _width(0)
	, _height(0)
{

}

Context::~Context()
{
	
}

bool Context::Init(uint width, uint height)
{
	_width = width;
	_height = height;

#ifdef WIN32
	_instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

#ifndef FINAL
	if(!CreateConsole())
	{
		LogErrorL("Failed to create console window");
		return false;
	}
#endif

	WNDCLASSEX wc;

	memclr(&wc, sizeof(wc));

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = _instance;
    wc.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
    wc.lpszMenuName  = nullptr;
    wc.lpszClassName = "EngineClass";
    wc.hIconSm       = wc.hIcon;

    if(!RegisterClassEx(&wc))
    {
        LogErrorL("Failed to register class: %s", wc.lpszClassName);
        return false;
    }

	LPSTR window_title = "Engine";
    _window = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        wc.lpszClassName,
        window_title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        nullptr, nullptr, _instance, nullptr);

    if(_window == nullptr)
    {
        LogErrorL("Failed to create window: %s", window_title);
        return false;
    }

	LogSuccessL("Created window: %s", window_title);

	SendMessage(_window, WM_CREATED, 0, 0);

    ShowWindow(_window, SW_SHOWNORMAL);
    UpdateWindow(_window);
#elif defined(ANDROID)
	Core::GetInstance().GetState()->onAppCmd = android_handle_cmd;
#endif

	return true;
}

void Context::Destroy()
{
#if !defined(FINAL) && defined(WIN32)
	DestroyConsole();
#endif

	LogMessageL("Destroyed context");
}

#ifdef WIN32
bool Context::CreateConsole()
{
	if(AllocConsole())
	{
		int input_handle = _open_osfhandle(reinterpret_cast<intptr_t>(GetStdHandle(STD_INPUT_HANDLE)), _O_TEXT);
        int output_handle = _open_osfhandle(reinterpret_cast<intptr_t>(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT);
		int error_handle = _open_osfhandle(reinterpret_cast<intptr_t>(GetStdHandle(STD_ERROR_HANDLE)), _O_TEXT);
        *stdin = *_fdopen(input_handle, "r");
        *stdout = *_fdopen(output_handle, "w");
		*stderr = *_fdopen(error_handle, "w");
		return true;
	}

	return false;
}

void Context::DestroyConsole()
{
	fclose(stdout);
	fclose(stdin);
	fclose(stderr);
	FreeConsole();
}
#endif