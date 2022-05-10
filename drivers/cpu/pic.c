#include <libc/types.h>

#include "cpu.h"

void _pic_remap_io(uint16_t port, uint8_t data);

void pic_remap() {
    uint8_t pic1_mask = 0xFC;
    uint8_t pic2_mask = 0xFF;

    _pic_remap_io(PORT_PIC1_CTRL, 0x11);
    _pic_remap_io(PORT_PIC2_CTRL, 0x11);

    _pic_remap_io(PORT_PIC1_DATA, 0x20);
    _pic_remap_io(PORT_PIC2_DATA, 0x28);

    _pic_remap_io(PORT_PIC1_DATA, 0x4);
    _pic_remap_io(PORT_PIC2_DATA, 0x2);

    _pic_remap_io(PORT_PIC1_DATA, 0x1);
    _pic_remap_io(PORT_PIC2_DATA, 0x1);

    _pic_remap_io(PORT_PIC1_DATA, 0xFC);
    _pic_remap_io(PORT_PIC2_DATA, 0xFF);
}

void pic_send_eoi() {
    port_byte_out(PORT_PIC1_CTRL, 0x20);
    port_byte_out(PORT_PIC2_CTRL, 0x20);
}

uint8_t pic_read_ir() {
    port_byte_out(PORT_PIC1_CTRL, 0xA);
    uint8_t result = port_byte_in(PORT_PIC1_CTRL);

    return result;
}

uint8_t pic_read_is() {
    port_byte_out(PORT_PIC1_CTRL, 0xB);
    uint8_t result = port_byte_in(PORT_PIC1_CTRL);

    return result;
}

void _pic_remap_io(uint16_t port, uint8_t data) {
    port_byte_out(port, data);
    port_io_wait();
}