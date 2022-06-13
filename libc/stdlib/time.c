#include <kernel/kernel.h>
#include <libc/libc.h>

void sleep(uint32_t ms) {
    uint32_t ctick = pit_tick;

    while (ms > 0) {
        __asm__("hlt");
        if (ctick != pit_tick)
            ms--;
    }
}