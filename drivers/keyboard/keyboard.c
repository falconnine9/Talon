#include <drivers/cpu/cpu.h>
#include <kernel/interrupts/interrupts.h>
#include <libc/io.h>
#include <libc/types.h>

#include "keyboard.h"

static kbd_callback_t _kbd_callback = NULL;

void kbd_init() {
    idt_register_entry(KBD_IRQ_VECT, kbd_irq_handler);
}

void kbd_set_waiting_key(kbd_callback_t dispatch) {
    _kbd_callback = dispatch;
}

void kbd_clear_waiting_key() {
    _kbd_callback = NULL;
}

void kbd_irq_handler() {
    uint8_t sc = port_byte_in(PORT_KBD_DATA);
    if (_kbd_callback != NULL) {
        _kbd_callback(sc);
    }

    pic_send_eoi(KBD_IRQ_VECT - 0x20);
    __asm__("leave");
    __asm__("iret");
}