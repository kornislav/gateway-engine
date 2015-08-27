#include "Core.h"
#include "Context.h"
#include <Renderer/Graphics.h>

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

bool Core::Init(uint width, uint height)
{
	if(!_context->Init(width, height))
	{
		return false;
	}

	if(!_graphics->Init(_context))
	{
		return false;
	}

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
		PeekMessage(&_msg, _context->GetWindow(), 0, 0, PM_REMOVE);

        if (_msg.message == WM_QUIT)
        {
			_quit = true;
        }
        else
        {
            TranslateMessage(&_msg);
            DispatchMessage(&_msg);
        }
#endif
    }
}