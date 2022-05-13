#include <libc/types.h>

#include "cpu.h"

static inline void _pic_remap_io(uint16_t port, uint8_t data);

void pic_remap() {
    _pic_remap_io(PORT_PIC1_CTRL, PIC_ICW_INIT);
    _pic_remap_io(PORT_PIC2_CTRL, PIC_ICW_INIT);

    _pic_remap_io(PORT_PIC1_DATA, PIC_ICW_LOW_OFFSET);
    _pic_remap_io(PORT_PIC2_DATA, PIC_ICW_HIGH_OFFSET);

    _pic_remap_io(PORT_PIC1_DATA, PIC_ICW_CASCADE1);
    _pic_remap_io(PORT_PIC2_DATA, PIC_ICW_CASCADE2);

    _pic_remap_io(PORT_PIC1_DATA, PIC_ICW_X86);
    _pic_remap_io(PORT_PIC2_DATA, PIC_ICW_X86);
}

void pic_send_eoi(uint8_t irq) {
    port_byte_out(PORT_PIC1_CTRL, 0x20);

    if (irq >= 8)
        port_byte_out(PORT_PIC2_CTRL, 0x20);
}

void pic_set_mask(uint8_t mask, uint8_t pic) {
    uint16_t port = pic == 0 ? PORT_PIC1_DATA : PORT_PIC2_DATA;
    port_byte_out(port, mask);
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

static inline void _pic_remap_io(uint16_t port, uint8_t data) {
    port_byte_out(port, data);
    port_io_wait();
}