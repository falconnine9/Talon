#include <libc/libc.h>

#include "vga.h"

void vga_outc(uint8_t x, uint8_t y, uint16_t c) {
    _vga_buf[y * VGA_WIDTH + x] = c;
}

void vga_outs(uint8_t x, uint8_t y, string_t s, uint8_t attr) {
    char c;
    while ((c = *s++) != '\0') {
        if (c >= 32 && c <= 126)
            vga_outc(x, y, VGA_CHAR(c, attr));
    }
}

void vga_setattr(uint8_t x, uint8_t y, uint8_t attr) {
    uint8_t c = (uint8_t)(_vga_buf[y * VGA_WIDTH + x] & 0xFF);
    _vga_buf[y * VGA_WIDTH + x] = VGA_CHAR(c, attr);
}