#include "Core.h"
#include "Context.h"
#include <Renderer/Graphics.h>
#ifdef ANDROID
#include <android/looper.h>
#include <android/android_native_app_glue.h>

android_app* Core::_state = nullptr;
#endif

Core::Core()
	: _quit(false)
{
	_context = new Context();
	_graphics = new Graphics();
}

Core::~Core()
{
	delete _graphics;
	delete _context;
}

#ifdef ANDROID
bool Core::Init(android_app* state)
#else
bool Core::Init()
#endif
{
#ifdef ANDROID
	_state = state;
#endif

	// THIS IS HARDCODED, PLS CHANGE
	if(!_context->Init(1280, 720))
	{
		return false;
	}

#ifndef ANDROID
	if(!_graphics->Init(_context))
	{
		return false;
	}
#endif

	return true;
}

void Core::Destroy()
{
	_graphics->Destroy();
	_context->Destroy();
}

void Core::Run()
{
	while(!_quit)
    {
#ifdef WIN32
		while (PeekMessage(&_msg, _context->GetWindow(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_msg);
			DispatchMessage(&_msg);
		}

		if (PeekMessage(&_msg, 0, WM_QUIT, WM_QUIT, PM_NOREMOVE))
		{
			_quit = true;
		}
#elif defined(ANDROID)
		int events;
		android_poll_source* pSource = nullptr;
		int ident = ALooper_pollAll(0, 0, &events, (void**)&pSource);
		if (ident >= 0)
		{
			if(pSource)
			{
				pSource->process(_state, pSource);
			}

			if(_state->destroyRequested)
			{
				_quit = true;
			}
		}
#endif
    }
}