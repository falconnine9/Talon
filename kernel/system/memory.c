#include <kernel/kernel.h>
#include <libc/libc.h>

#include "sys.h"

/*********************
 * System call masks *
 *********************/

void sysmask_malloc() {
    uint32_t ret_ptr;
    uint32_t size;
    __asm__("movl %%ebx, %0" : "=r"(ret_ptr));
    __asm__("movl %%ecx, %0" : "=r"(size));

    sys_malloc((void*)ret_ptr, (size_t)size);
}

void sysmask_mfree() {
    uint32_t blk_ptr;
    __asm__("movl %%ebx, %0" : "=r"(blk_ptr));

    sys_mfree((void*)blk_ptr);
}

/***********************
 * System call methods *
 ***********************/

void sys_malloc(void* ptr, size_t size) {
    *(byte**)ptr = mm_alloc_block(size);
}

void sys_mfree(void* ptr) {
    mm_dealloc_block((void*)((uint32_t)ptr - sizeof(mm_block_t)));
}