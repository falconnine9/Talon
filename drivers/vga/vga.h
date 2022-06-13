#ifndef _VGA_H
#define _VGA_H 1

#include <libc/libc.h>

typedef uint16_t* vga_buf_t;

#define VGA_CHAR(c, attr)    (attr << 8 | c)
#define VGA_ATTR(fore, back) (back << 4 | fore)

#define VGA_OFFSET 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

#define VGA_BLACK    0x0
#define VGA_BLUE     0x1
#define VGA_GREEN    0x2
#define VGA_CYAN     0x3
#define VGA_RED      0x4
#define VGA_PINK     0x5
#define VGA_BROWN    0x6
#define VGA_WHITE    0x7
#define VGA_GRAY     0x8
#define VGA_BLUE_LI  0x9
#define VGA_GREEN_LI 0xA
#define VGA_CYAN_LI  0xB
#define VGA_RED_LI   0xC
#define VGA_PINK_LI  0xD
#define VGA_YELLOW   0xE
#define VGA_WHITE_LI 0xF

#define PORT_VGACUR_CTRL 0x3D4
#define PORT_VGACUR_DATA 0x3D5

extern volatile vga_buf_t _vga_buf;

void vga_outc(uint8_t x, uint8_t y, uint16_t c);
void vga_outs(uint8_t x, uint8_t y, string_t s, uint8_t attr);
void vga_setattr(uint8_t x, uint8_t y, uint8_t attr);

void     vga_disablecur();
void     vga_enablecur();
void     vga_setcur(uint8_t x, uint8_t y);
uint16_t vga_getcur();

void vga_cpybuf(vga_buf_t dst);
void vga_setbuf(vga_buf_t src);

#endif