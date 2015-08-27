#include "Context.h"
#include <iostream>

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

	WNDCLASSEX wc;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = _instance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "EngineClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        std::cerr << "Failed to register window class" << std::endl;
        return false;
    }

    // Step 2: Creating the Window
    _window = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EngineClass",
        "Gateway",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, _instance, NULL);

    if(_window == NULL)
    {
        std::cerr << "Failed to create window" << std::endl;
        return false;
    }

    ShowWindow(_window, SW_SHOWNORMAL);
    UpdateWindow(_window);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
#endif

	return true;
}