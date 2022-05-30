#ifndef _VGA_H
#define _VGA_H 1

#include <libc/types.h>

typedef uint8_t vga_pixel_t;

#define VGA_OFFSET 0xA0000
#define VGA_WIDTH  320
#define VGA_HEIGHT 200

#define VGA_POS(x, y)  (y | x << 16)
#define VGA_RECT(w, h) (h | w << 16)

void vga_draw_rect(uint32_t pos, uint32_t dims, vga_pixel_t col);
void vga_draw_square(uint32_t pos, uint16_t dim, vga_pixel_t col);

#endif