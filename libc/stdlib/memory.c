#include <kernel/kernel.h>
#include <libc/libc.h>

void* malloc(size_t size) {
    void* ptr;
    sys_malloc(ptr, size);
    return ptr;
}

void free(void* ptr) {
    sys_mfree(ptr);
}