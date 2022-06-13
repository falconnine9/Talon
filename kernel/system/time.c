#include <drivers/cpu/cpu.h>
#include <libc/types.h>

#include "sys.h"

void sys_sleep(uint32_t ms) {
    uint32_t ctick = pit_tick;

    while (ms > 0) {
        __asm__("hlt");
        if (ctick != pit_tick)
            ms--;
    }
}