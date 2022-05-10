#include <libc/io.h>
#include <libc/types.h>

#include "cpu.h"

extern void* isr_table[IDT_ISR_MAX];

static idt_desc_t _idt[IDT_SIZE];
static idt_reg_t  _idtr;

void idt_load_isrtable() {
    for (uint8_t i = 0; i < IDT_ISR_MAX; i++) {
        idt_register_entry(i, isr_table[i]);
    }

    __asm__("lidt %0" :: "m"(_idtr));
}

void idt_isr_handler(uint8_t code) {
    char code_str[5];
    str_fi(code_str, code);

    prints("Interrupt called: ");
    prints(code_str);
    printc('\n');
}

void idt_register_entry(uint8_t vect, void* handler) {
    idt_construct_entry(&_idt[vect], handler);
}

void idt_construct_entry(idt_desc_t* entry, void* handler) {
    entry->base_low  = (uint16_t)((uint32_t)handler & 0xFFFF);
    entry->base_high = (uint16_t)((uint32_t)handler >> 8);

    entry->segment = GDT_KCODE_SEG;
    entry->flags   = IDT_DEF_FLAGS;

    entry->reserved = 0;
}