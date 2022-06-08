#include <kernel/kernel.h>
#include <libc/types.h>

#include "sys.h"

void* sys_malloc(size_t size) {
    void* ptr = mm_alloc_block(size);
    return (void*)((uint32_t)ptr + sizeof(mm_block_t));
}

void sys_mfree(void* ptr) {
    mm_dealloc_block((void*)((uint32_t)ptr - sizeof(mm_block_t)));
}