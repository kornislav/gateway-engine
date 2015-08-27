#include "Core.h"
#include "Context.h"

Core::Core()
{
	_context = new Context();
}

Core::~Core()
{
	delete _context;
}

bool Core::Init(uint width, uint height)
{
	if(!_context->Init(width, height))
	{
		LogErrorL("Failed to create context");
		return false;
	}
}

void Core::Destroy()
{
	_context->Destroy();
}