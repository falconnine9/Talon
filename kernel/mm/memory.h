#ifndef _MEMORY_H
#define _MEMORY_H

#include <libc/def.h>
#include <libc/types.h>

typedef struct {
    uint8_t used  : 1;
    uint8_t som   : 1;
    uint8_t eom   : 1;
    uint8_t pused : 1;
    uint8_t nused : 1;
    uint8_t res   : 3;
} packed mm_flags_t;

typedef struct {
    uint32_t   limit;
    uint32_t   low;
    mm_flags_t flags;
} packed mm_block_t;

#define mm_limit(blk, shif) (blk->limit << shif)

extern size_t _mm_heap_size;

void  mm_init();
void* mm_alloc_block(size_t size);
void  mm_dealloc_block(void* ptr);
void* mm_get_addr(void* ptr, uint32_t index);

mm_block_t mm_make_block(uint32_t limit, uint32_t low, mm_flags_t flags);
mm_flags_t mm_make_flags(bool_t used, bool_t som, bool_t eom, bool_t pused, bool_t nused);

#endif