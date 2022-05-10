#include <libc/types.h>

#include "cpu.h"

uint8_t port_byte_in(uint16_t port) {
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

void port_byte_out(uint16_t port, uint8_t data) {
    __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

void port_io_wait() {
    for (int i = 0; i < 32; i++)
        __asm__("nop");
}