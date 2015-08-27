#include "Context.h"
#include <System/Logger.h>

#ifdef WIN32
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#endif

#ifdef WIN32
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
#endif

Context::Context()
{

}

Context::~Context()
{
	
}

bool Context::Init(uint width, uint height)
{
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
    MSG Msg;

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

    ShowWindow(_window, SW_SHOWNORMAL);
    UpdateWindow(_window);

	while(GetMessage(&Msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
#endif

	return true;
}

void Context::Destroy()
{
#ifndef FINAL
	DestroyConsole();
#endif
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
}
#endif