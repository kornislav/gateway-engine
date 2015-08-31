#pragma once

#include <cstring>

static void memclr(void* data, size_t size)
{
	memset(data, 0, size);
}