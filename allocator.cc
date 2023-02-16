#include "allocator.h"
#include "assert.h"

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
    auto it = freelist.begin();
    Block* to_alloc;
    while(it != freelist.end() && to_alloc == nullptr) {
        if ((*it)->block_size >= bytes) {
            to_alloc = *it;
            it = freelist.erase(it);
        }
        it++;
    }
    assert(to_alloc != nullptr);

    if (to_alloc->block_size > bytes) {
        // Fragment blocks
        auto new_block = new Block(to_alloc->block_size - bytes, to_alloc + bytes);
        freelist.push_back(new_block);
    }

    allocated.push_back(to_alloc);
    return to_alloc->start;
    
}

void Allocator::free(void* ptr) {
    for (auto it = allocated.begin(); it < allocated.end(); it++) {
        if ((*it)->start == ptr) {
            freelist.push_back(*it);
            allocated.erase(it);
        }
    }
    for (auto it = freelist.begin(); it < freelist.end(); it++) {
        // Search for blocks to coalesce
        if ((*it)->start + (*it)->block_size == (*(it+1))->start) {
            (*it)->block_size += (*(it+1))->block_size;
            delete *(it+1);
            it = freelist.erase(it+1);
        }
    }
}