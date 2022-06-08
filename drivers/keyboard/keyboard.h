#ifndef _KEYBOARD_H
#define _KEYBOARD_H 1

#include <libc/def.h>
#include <libc/types.h>

typedef struct _packed {
    uint16_t code;
    bool_t   up;
 } keypress_t;

typedef void(*kbd_callback_t)(uint16_t);

#define PORT_KBD_CTRL   0x64
#define PORT_KBD_DATA   0x60
#define PORT_KBD_STATUS 0x64

#define KBD_CODE_SIZE 51
#define KBD_IRQ_VECT  0x21

// Control buttons
#define KBD_LSHIFT_DOWN 0x2A
#define KBD_LSHIFT_UP   0xAA
#define KBD_RSHIFT_DOWN 0x36
#define KBD_RSHIFT_UP   0xB6
#define KBD_ALT_DOWN    0x38
#define KBD_ALT_UP      0xB8
#define KBD_CTRL_DOWN   0x1D
#define KBD_CTRL_UP     0x9D

extern void kbd_irq();

void kbd_init();
void kbd_swk(kbd_callback_t dispatch);
void kbd_cwk();
void kbd_irq_handler();

char kbd_gkc(uint8_t code, bool_t shifted);

#endif