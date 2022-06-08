#ifndef _MEMORY_H
#define _MEMORY_H

#include <libc/def.h>
#include <libc/types.h>

typedef struct _packed {
    uint8_t used  : 1;
    uint8_t som   : 1;
    uint8_t eom   : 1;
    uint8_t pused : 1;
    uint8_t nused : 1;
    uint8_t res   : 3;
} mm_flags_t;

typedef struct _packed {
    uint32_t   limit;
    uint32_t   low;
    mm_flags_t flags;
} mm_block_t;

extern size_t         _mm_heap_size;
extern volatile void* _mm_heap_offset;

void  mm_init(size_t heap_size, uint32_t heap_offset);
void* mm_alloc_block(size_t size);
void  mm_dealloc_block(void* ptr);

mm_block_t mm_make_block(uint32_t limit, uint32_t low, mm_flags_t flags);
mm_flags_t mm_make_flags(bool_t used, bool_t som, bool_t eom, bool_t pused, bool_t nused);

#endif