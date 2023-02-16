#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstdint>
#include <vector>

struct Block {
    unsigned block_size;
    void* start;

    Block(unsigned block_size, void* start): block_size(block_size), start(start) {}
};

class Allocator {
public:
    Allocator(unsigned bytes);
    ~Allocator();
    void* malloc(unsigned bytes);
    void free(void* ptr);

private:
    std::vector<Block*> freelist;
    std::vector<Block*> allocated;
    
    uint8_t* memory;
};

#endif 