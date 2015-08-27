#pragma once

// includes
#ifdef WIN32
#include <windows.h>
#endif

// typedefs
typedef unsigned int uint;

// macros

// functions
static void memclr(void* data, size_t size)
{
	memset(data, 0, size);
}