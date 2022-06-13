#include <libc/libc.h>

#include "vga.h"

volatile vga_buf_t _vga_buf = (volatile vga_buf_t)VGA_OFFSET;

void vga_cpybuf(vga_buf_t dst) {
    for (uint16_t off = 0; off < VGA_WIDTH * VGA_HEIGHT; off++)
        dst[off] = _vga_buf[off];
}

void vga_setbuf(vga_buf_t src) {
    for (uint16_t off = 0; off < VGA_WIDTH * VGA_HEIGHT; off++)
        _vga_buf[off] = src[off];
}