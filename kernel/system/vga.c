#include <drivers/vga/vga.h>
#include <libc/libc.h>

#include "sys.h"

/*********************
 * System call masks *
 *********************/

void sysmask_putc() {
    uint8_t  x;
    uint8_t  y;
    uint16_t c;
    __asm__("mov %%bl, %0" : "=r"(x));
    __asm__("mov %%bh, %0" : "=r"(y));
    __asm__("mov %%cx, %0" : "=r"(c));

    sys_putc(x, y, c);
}

void sysmask_getvgacur() {
    uint32_t x_ptr;
    uint32_t y_ptr;
    __asm__("movl %%ebx, %0" : "=r"(x_ptr));
    __asm__("movl %%ecx, %0" : "=r"(y_ptr));

    sys_getvgacur((uint8_t*)x_ptr, (uint8_t*)y_ptr);
}

void sysmask_setvgacur() {
    uint8_t x;
    uint8_t y;
    __asm__("mov %%bl, %0" : "=r"(x));
    __asm__("mov %%bh, %0" : "=r"(y));

    sys_setvgacur(x, y);
}

/***********************
 * System call methods *
 ***********************/

void sys_putc(uint8_t x, uint8_t y, uint16_t c) {
    vga_outc(x, y, c);
}

void sys_getvgacur(uint8_t* x, uint8_t* y) {
    uint16_t offset = vga_getcur();
    *x = (uint8_t)(offset >> 8);
    *y = (uint8_t)(offset & 0xFF);
}

void sys_setvgacur(uint8_t x, uint8_t y) {
    vga_setcur(x, y);
}