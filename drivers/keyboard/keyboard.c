#include <drivers/cpu/cpu.h>
#include <kernel/kernel.h>
#include <libc/def.h>
#include <libc/types.h>

#include "keyboard.h"

static kbd_callback_t _kbd_callback = NULL;

void kbd_init() {
    idt_register_entry(KBD_IRQ_VECT, kbd_irq);
}

void kbd_swk(kbd_callback_t dispatch) {
    _kbd_callback = dispatch;
}

void kbd_cwk() {
    _kbd_callback = NULL;
}

void kbd_irq_handler() {
    uint16_t sc = port_byte_in(PORT_KBD_DATA);

    if (_kbd_callback != NULL)
        _kbd_callback(sc);

    pic_send_eoi(KBD_IRQ_VECT - 0x20);
}