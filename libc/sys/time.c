#include <drivers/cpu/cpu.h>
#include <libc/sys.h>

void sys_sleep(uint32_t ms) {
    uint32_t ms_tick = 0;
    uint32_t interval_tick = 0;

    while (TRUE) {
        interval_tick = pit_get_tick();
        __asm__("hlt");

        if (interval_tick != pit_get_tick())
            ms_tick++;
        
        if (ms_tick >= ms)
            break;
    }
}