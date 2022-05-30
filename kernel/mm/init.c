#include <kernel/kernel.h>
#include <libc/types.h>

#include "memory.h"

size_t _mm_heap_size;

void mm_init(size_t heap_size) {
    _mm_heap_size = heap_size;
    mm_block_t initial_blk = {
        .limit = heap_size,
        .low   = NULL,
        .flags = mm_make_flags(0, 1, 1, 0, 0)
    };
    *(volatile mm_block_t*)HEAP_OFFSET = initial_blk;
}