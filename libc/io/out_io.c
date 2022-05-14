#include <drivers/vga/vga.h>
#include <libc/io.h>
#include <libc/types.h>

void prints_col(string_t str, vga_attr_t attr) {
    vga_attr_t col = vga_get_attr();

    vga_set_attr(attr);
    prints(str);
    vga_set_attr(col);
}

void printc_col(char c, vga_attr_t attr) {
    vga_attr_t col = vga_get_attr();
    
    vga_set_attr(attr);
    printc(c);
    vga_set_attr(col);
}

void prints(string_t str) {
    char c;
    int32_t offset = -1;

    while ((c = *str++) != '\0')
        offset = vgabuff_output_c(c, offset);
    
    if (offset != -1)
        set_cursor_off(offset);
}

void printc(char c) {
    set_cursor_off(vgabuff_output_c(c, -1));
}