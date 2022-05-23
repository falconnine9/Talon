#include <libc/types.h>

#include "vga.h"

static vga_attr_t _attr = VGA_COMBINE_ATTR(VGA_WHITE, VGA_BLACK);

vga_attr_t vga_get_attr() {
    return _attr;
}

void vga_set_attr(vga_attr_t attr) {
    _attr = attr;
}