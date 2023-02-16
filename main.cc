#include <iostream>

#include "allocator_wrapper.h"

#define MEM_SIZE 1024

int main() {
	auto my_allocator = new AllocatorWrapper(MEM_SIZE);
	my_allocator->PrintMemState();

	void* p1 = my_allocator->malloc(100);
	my_allocator->PrintMemState();
	my_allocator->free(p1);
	my_allocator->PrintMemState();

	
	return 0;
}
