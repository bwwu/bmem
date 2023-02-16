#include <iostream>
#include <vector>
#include <cstdint>

#include "allocator_wrapper.h"


AllocatorWrapper::AllocatorWrapper(int bytes): Allocator(bytes) {}

void PrintBlocks(void* startptr, const std::vector<Block*>& blocklist) {
	int i = 0;
	for (auto block: blocklist) {
		std::cout << "\tBlock " << i++ << std::endl;
		std::cout << "\t\tStartAddr:\t" << static_cast<uint8_t*>(block->start) - static_cast<uint8_t*>(startptr);
		std::cout << "\tSize:\t" << block->block_size << std::endl;
	}
}

void AllocatorWrapper::PrintMemState() {
	for (int i=0; i<80; i++) {
		std::cout << "=";
	}
	std::cout << "\nBLOCKS IN FREE LIST: "  << freelist.size() << std::endl;
	PrintBlocks(memory, freelist);
	
	std::cout << "BLOCKS IN ALLOCATED LIST: " << allocated.size() << std::endl;
	PrintBlocks(memory, allocated);
}


