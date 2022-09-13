#ifndef _ALLOCATION_TRACER_
#define _ALLOCATION_TRACER_

#include<iostream>
#include"Logger.h"

void* operator new(size_t size)
{
	Logger::Warn("Allocating : %d bytes", size);
	if (size > 20000)
		__debugbreak();
	return malloc(size);
}
#endif