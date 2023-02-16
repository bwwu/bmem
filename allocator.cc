#include "allocator.h"

Allocator::Allocator(unsigned bytes) {
    memory = new uint8_t(bytes);
    freelist.push_back(new Block(bytes, memory));
}

Allocator::~Allocator() {
    for (auto block: freelist) {
        delete block;
    }
    delete memory;
}

void* Allocator::malloc(unsigned bytes) {

    return nullptr;
}

void Allocator::free(void* ptr) {}