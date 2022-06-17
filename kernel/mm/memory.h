#ifndef _MEMORY_H
#define _MEMORY_H

#include <libc/libc.h>

typedef struct {
    uint32_t flags        : 13;
    uint32_t address_high : 4;
    uint32_t reserved     : 5;
    uint32_t address_low  : 10;
} __attribute__((packed)) mm_pde_t;

extern mm_pde_t mm_pd[1024];
extern void     mm_enable();

void mm_init();
void mm_pagealloc();

#endif