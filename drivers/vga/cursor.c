#include <drivers/cpu/cpu.h>

#include "vga.h"

uint16_t vgacur_get_offset() {
    uint16_t offset;

    port_byte_out(PORT_VGA_CTRL, 14);
    offset = port_byte_in(PORT_VGA_DATA) << 8;

    port_byte_out(PORT_VGA_CTRL, 15);
    offset += port_byte_in(PORT_VGA_DATA);

    return offset;
}

void vgacur_set_offset(uint16_t offset) {
    port_byte_out(PORT_VGA_CTRL, 14);
    port_byte_out(PORT_VGA_DATA, (uint8_t)(offset >> 8));

    port_byte_out(PORT_VGA_CTRL, 15);
    port_byte_out(PORT_VGA_DATA, (uint8_t)(offset & 0xFF));
}