#include <kernel/interrupts/interrupts.h>
#include <libc/def.h>
#include <libc/io.h>
#include <libc/types.h>

#include "cpu.h"

static uint32_t _tick     = 0;
static uint32_t _interval = 0;

void pit_init() {
    idt_register_entry(PIT_IRQ_VECT, pit_irq_handler);

    uint16_t freq = 1193182 / PIT_FREQUENCY;

    port_byte_out(PORT_PIT_CTRL, 0x36);
    port_byte_out(PORT_PIT_COUNTER, (uint8_t)(freq & 0xFF));
    port_byte_out(PORT_PIT_COUNTER, (uint8_t)(freq >> 8));
}

naked void pit_irq_handler() {
    __asm__("pushal");
    _tick++;

    if (_tick == PIT_INTERVAL_LEN) {
        _tick = 0;
        _interval++;
    }

    pic_send_eoi(PIT_IRQ_VECT - 0x20);
    __asm__("popal");
    __asm__("iret");
}

uint32_t pit_get_tick() {
    return _tick;
}