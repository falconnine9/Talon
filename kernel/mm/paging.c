#include <kernel/kernel.h>
#include <libc/libc.h>

#include "memory.h"

mm_pde_t mm_pd[1024] __attribute__((aligned(4096)));

static mm_pde_t _default_pde = {
    .flags        = 0x87,
    .address_low  = 0x00,
    .address_high = 0x00,
    .reserved     = 0x00
};

void mm_init() {
    uint32_t cr3_reg = (uint32_t)mm_pd;
    uint32_t real_ml = k_ml - k_ml % 0x400000;

    uint16_t j = 0;
    for (uint32_t i = 0; i < real_ml; i += 0x400000) {
        _default_pde.address_low  = (i >> 22) & (0xFF + 0b11);
        mm_pd[j++] = _default_pde;
    }

    mm_pd[0].flags |= (1 << 6);
    mm_enable();
}

void mm_pagealloc() {
    
}