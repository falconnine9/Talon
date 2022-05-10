#ifndef _KEYBOARD_H
#define _KEYBOARD_H 1

#include <libc/types.h>

typedef void(*dispatch_func_t)(uint8_t);

#define KBD_CODE_SIZE 51
#define KBD_IRQ_VECT  0x21

#define KBD_LSHIFT_DOWN 0x2A
#define KBD_LSHIFT_UP   0xAA

#define KBD_RSHIFT_DOWN 0x36
#define KBD_RSHIFT_UP   0xB6

#define KBD_ALT_DOWN    0x38
#define KBD_ALT_UP      0xB8

void kbd_init();
void kbd_set_waiting_key(dispatch_func_t dispatch);
void kbd_clear_waiting_key();
void kbd_irq_handler();

char kbd_get_key_char(uint8_t code, bool_t shifted);

#endif