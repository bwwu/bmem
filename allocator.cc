#include "allocator.h"
#include "assert.h"

Allocator::Allocator(int bytes) {
    memory = new uint8_t(bytes);
    freelist.push_back(new Block(bytes, memory));
}

Allocator::~Allocator() {
    for (auto block : freelist) {
        delete block;
    }
    delete memory;
}

void *Allocator::malloc(int bytes) {
    auto it = freelist.begin();
    Block* to_alloc;
    while (it != freelist.end() && to_alloc == nullptr) {
        if ((*it)->block_size >= bytes) {
            to_alloc = *it;
            it = freelist.erase(it);
        }
        it++;
    }
    assert(to_alloc != nullptr);

    if (to_alloc->block_size > bytes) {
        // Fragment blocks
        auto new_block = new Block(
            to_alloc->block_size - bytes,
            static_cast<uint8_t*>(to_alloc->start) + bytes);
        freelist.push_back(new_block);
    }

    allocated.push_back(to_alloc);
    return to_alloc->start;
}

void Allocator::free(void* ptr) {
    Block* to_insert;
    for (auto it = allocated.begin(); it < allocated.end(); it++) {
        if ((*it)->start == ptr) {
            to_insert = *it;
            allocated.erase(it);
            break;
        }
    }

    // Insert back into freelist in asc order of start addr
    auto it = freelist.begin();
    while (it < freelist.end() && (*it)->start < to_insert->start) {
        it++;
    }
    freelist.insert(it, to_insert);

    for (auto it = freelist.begin(); it < freelist.end(); it++) {
        // Search for blocks to coalesce
        if ((*it)->start + (*it)->block_size == (*(it + 1))->start) {
            (*it)->block_size += (*(it + 1))->block_size;
            delete *(it + 1);
            it = freelist.erase(it + 1);
        }
    }
}
