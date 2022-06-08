#include <libc/types.h>

#include "memory.h"

size_t         _mm_heap_size;
volatile void* _mm_heap_offset;

void mm_init(size_t heap_size, uint32_t heap_offset) {
    _mm_heap_size   = heap_size;
    _mm_heap_offset = (volatile void*)heap_offset;

    mm_block_t initial_blk = {
        .limit = heap_size,
        .low   = NULL,
        .flags = mm_make_flags(0, 1, 1, 0, 0)
    };
    *(volatile mm_block_t*)heap_offset = initial_blk;
}