#include <drivers/vga/vga.h>
#include <libc/types.h>

#include "sys.h"

void sys_print(string_t msg) {
    sys_printcol(msg, VGA_ATTR(VGA_WHITE_LI, VGA_BLACK));
}

void sys_printcol(string_t msg, uint8_t attr) {
    uint16_t cur_pos = vga_getcur();
    uint8_t  cur_x   = (uint8_t)(cur_pos >> 8);
    uint8_t  cur_y   = (uint8_t)(cur_pos & 0xFF);
    char     c;

    while ((c = *msg++) != '\0') {
        if (c == '\n') {
            cur_x = 0;
            cur_y++;
        }
        else {
            vga_outc(cur_x, cur_y, VGA_CHAR(c, attr));
            if (cur_x == VGA_WIDTH - 1) {
                cur_x = 0;
                cur_y++;
            }
            else
                cur_x++;
        }
    }

    vga_setcur(cur_x, cur_y);
}