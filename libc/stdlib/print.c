#include <drivers/vga/vga.h>
#include <kernel/kernel.h>
#include <libc/libc.h>

void print(string_t msg) {
    printcol(msg, VGA_ATTR(VGA_WHITE_LI, VGA_BLACK));
}

void printcol(string_t msg, uint8_t attr) {
    uint8_t  cur_x;
    uint8_t  cur_y;
    char     c;
    sys_getvgacur(&cur_x, &cur_y);

    while ((c = *msg++) != '\0') {
        if (c == '\n') {
            cur_x = 0;
            cur_y++;
        }
        else {
            sys_putc(cur_x, cur_y, VGA_CHAR(c, attr));
            if (cur_x == VGA_WIDTH - 1) {
                cur_x = 0;
                cur_y++;
            }
            else
                cur_x++;
        }
    }

    sys_setvgacur(cur_x, cur_y);
}