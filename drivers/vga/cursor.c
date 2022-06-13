#include <drivers/cpu/cpu.h>
#include <libc/libc.h>

#include "vga.h"

void vga_disablecur() {
    port_byte_out(PORT_VGACUR_CTRL, 0xA);
    port_byte_out(PORT_VGACUR_DATA, 0x20);
}

void vga_enablecur() {

}

void vga_setcur(uint8_t x, uint8_t y) {
    uint16_t offset = y * VGA_WIDTH + x;
    
    port_byte_out(PORT_VGACUR_CTRL, 14);
    port_byte_out(PORT_VGACUR_DATA, (uint8_t)(offset >> 8));

    port_byte_out(PORT_VGACUR_CTRL, 15);
    port_byte_out(PORT_VGACUR_DATA, (uint8_t)(offset & 0xFF));
}

uint16_t vga_getcur() {
    uint16_t offset;

    port_byte_out(PORT_VGACUR_CTRL, 14);
    offset |= port_byte_in(PORT_VGACUR_DATA) << 8;

    port_byte_out(PORT_VGACUR_CTRL, 15);
    offset |= port_byte_in(PORT_VGACUR_DATA);

    return (offset / VGA_WIDTH) | (offset % VGA_WIDTH) << 8;
}