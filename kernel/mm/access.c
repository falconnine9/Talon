#include <libc/types.h>

#include "memory.h"

void* mm_get_addr(void* ptr, uint32_t index) {
    mm_block_t* blk = ptr;
    if (index >= blk->limit) {
        __asm__("int $0x5");
        return NULL;
    }
    else
        return (void*)((uint32_t)ptr + sizeof(mm_block_t) + index);
}