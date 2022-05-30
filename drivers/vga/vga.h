/* Low level driver for the VGA buffer
 * 
 * Control Characters Supported:
 *  - \b: Moves the cursor offset back by 1
 *  - \n: Moves the cursor offset to the next line first position
 *  - \r: Moves the cursor offset to the first position on the same line
 *  - \t: Moves the cursor offset forward by 4
 * 
 * Supports 16 colors for the foreground and background.
 * A list of colors can be found below defined as header constants.
 * 
 * Has 2 streams for output, VGA_OUT and VGA_ERR. Right now they are
 * only for having pre-defined colors for output and output from either
 * of them can be enabled or disabled
 */

#ifndef _VGA_H
#define _VGA_H 1

#include <libc/types.h>

typedef uint8_t vga_attr_t;
typedef char*   vga_buff_t;

#define PORT_VGA_CTRL 0x3D4
#define PORT_VGA_DATA 0x3D5

#define VGA_OFFSET 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_SIZE   (VGA_WIDTH * VGA_HEIGHT)

#define CALC_ROW(offset)      (offset / VGA_WIDTH)
#define CALC_COLUMN(offset)   (offset % VGA_WIDTH)
#define CALC_OFFSET(row, col) (VGA_WIDTH * row + col)

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

#define VGA_COMBINE_ATTR(fore, back) (fore | back << 4)

void     vgabuff_fill(char c);
void     vgabuff_fill_row(char c, uint16_t row);
void     vgabuff_fill_col(char c, uint16_t col);
void     vgabuff_cpy(vga_buff_t buffer);
void     vgabuff_scroll(bool_t direction);
uint16_t vgabuff_output_c(char c, int32_t offset);

uint16_t vgacur_get_offset();
void     vgacur_set_offset(uint16_t offset);

vga_attr_t vga_get_attr();
void       vga_set_attr(vga_attr_t attr);

#endif