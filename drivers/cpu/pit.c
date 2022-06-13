#include <kernel/kernel.h>
#include <libc/def.h>
#include <libc/types.h>

#include "cpu.h"

uint32_t pit_tick = 0;

void pit_init() {
    idt_register_entry(PIT_IRQ_VECT, pit_irq);

    uint16_t freq = PIT_REAL_FREQ / PIT_INT_FREQ; // Interrupt every 1ms
    port_byte_out(PORT_PIT_CTRL, 0x36);
    port_byte_out(PORT_PIT_COUNTER, (uint8_t)(freq & 0xFF));
    port_byte_out(PORT_PIT_COUNTER, (uint8_t)(freq >> 8));
}

void pit_irq_handler() {
    if (pit_tick == UINT32_MAX)
        pit_tick = 0;
    else
        pit_tick++;
    
    pic_send_eoi(PIT_IRQ_VECT - 0x20);
}