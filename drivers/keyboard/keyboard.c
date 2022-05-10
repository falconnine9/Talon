#include <drivers/cpu/cpu.h>
#include <libc/io.h>
#include <libc/types.h>

#include "keyboard.h"

static bool_t          _waiting_key  = FALSE;
static dispatch_func_t _kbd_dispatch = NULL;

void kbd_init() {
    idt_register_entry(KBD_IRQ_VECT, kbd_irq_handler);
}

void kbd_set_waiting_key(dispatch_func_t dispatch) {
    _waiting_key  = TRUE;
    _kbd_dispatch = dispatch;
}

void kbd_clear_waiting_key() {
    _waiting_key  = FALSE;
    _kbd_dispatch = NULL;
}

void kbd_irq_handler() {
    __asm__("pusha");

    if (_waiting_key && _kbd_dispatch != NULL) {
        if (port_byte_in(0x64) & 0x1) {
            uint16_t sc = port_byte_in(0x60);
            _kbd_dispatch(sc);
        }
    }

    pic_send_eoi();
    __asm__("popa");
    __asm__("iret");
}