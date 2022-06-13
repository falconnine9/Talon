#include <libc/libc.h>

#include "memory.h"

void* mm_alloc_block(size_t size) {
    if (size > _mm_heap_size || size == 0) {
        __asm__("int $0xD");
        return NULL;
    }

    volatile void*       buf = _mm_heap_offset;
    volatile mm_block_t* blk = buf;
    while (blk->flags.used || blk->limit < size) {
        if (blk->flags.eom)
            return NULL;

        buf += blk->limit + sizeof(mm_block_t);
        blk  = buf;
    }

    mm_flags_t ext_flags = mm_make_flags(0, 0, blk->flags.eom, 1, blk->flags.nused);
    mm_flags_t blk_flags = mm_make_flags(1, blk->flags.som, 0, blk->flags.pused, 0);
    mm_block_t extension = mm_make_block(blk->limit - (size + sizeof(mm_block_t)), size, ext_flags);

    blk->limit = size;
    blk->flags = blk_flags;
    *(volatile mm_block_t*)((uint32_t)buf + blk->limit + sizeof(mm_block_t)) = extension;

    return (void*)buf;
}

void mm_dealloc_block(void* ptr) {
    if (ptr == NULL) {
        __asm__("int $0xD");
        return;
    }

    volatile mm_block_t* blk      = ptr;
    size_t               new_size = blk->limit;

    while (!blk->flags.nused && !blk->flags.eom) {
        ptr += blk->limit + sizeof(mm_block_t);
        blk  = ptr;
    }
    while (!blk->flags.pused && !blk->flags.som) {
        ptr      -= blk->low + sizeof(mm_block_t);
        blk       = ptr;
        new_size += blk->limit + sizeof(mm_block_t);
    }

    blk->limit = new_size - sizeof(mm_block_t);
    blk->flags = mm_make_flags(0, blk->flags.som, new_size == _mm_heap_size, 0, 0);
}