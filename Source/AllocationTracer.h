#ifndef _ALLOCATION_TRACER_
#define _ALLOCATION_TRACER_
#include<iostream>
#include"Logger.h"
void* operator new(size_t size)
{
	Logger::Error("Allocating : %d bytes", size);
	return malloc(size);
}
#endif