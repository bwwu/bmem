#ifndef ALLOCATOR_WRAPPER
#define ALLOCATOR_WRAPPER

#include "allocator.h"


class AllocatorWrapper : public Allocator {
public:
	AllocatorWrapper(int bytes);
	void PrintMemState();
};

#endif
