#ifndef _LIBC_IO_H
#define _LIBC_IO_H 1

#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>

#define get_out_attr()           vga_get_attr()
#define set_out_attr(fore, back) vga_set_attr(VGA_COMBINE_ATTR(fore, back))

#define get_cursor_off()         vgacur_get_offset()
#define set_cursor_pos(row, col) vgacur_set_offset(CALC_OFFSET(row, col))
#define set_cursor_off(offset)   vgacur_set_offset(offset)

void prints_col(string_t str, vga_attr_t attr);
void printc_col(char c, vga_attr_t attr);
void prints(string_t str);
void printc(char c);

char getc();
void gets(string_t dst);
void getkey(keypress_t* dst, bool_t catch);

#endif