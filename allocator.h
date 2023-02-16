#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstdint>
#include <vector>

struct Block {
    int block_size;
    void* start;

    Block(int block_size, void* start): block_size(block_size), start(start) {}
};

class Allocator {
public:
    Allocator(int bytes);
    ~Allocator();
    void* malloc(int bytes);
    void free(void* ptr);

protected:
    std::vector<Block*> freelist;
    std::vector<Block*> allocated;
    
    uint8_t* memory;
};

#endif 
