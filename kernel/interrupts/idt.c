#include <kernel/kernel.h>
#include <libc/types.h>

#include "interrupts.h"

extern void* isr_table[IDT_ISR_MAX];

static idt_desc_t _idt[IDT_SIZE];
static idt_reg_t  _idtr;

static string_t _isr_messages[IDT_MESSAGES] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check"
};

void idt_init() {
    for (uint16_t i = 0; i < IDT_SIZE; i++) {
        idt_register_entry(i, i < 32 ? isr_table[i] : idt_isr_overflow);
    }
}

void idt_set_register() {
    _idtr.limit = (uint16_t)(sizeof(idt_desc_t) * IDT_SIZE - 1);
    _idtr.base  = (uint32_t)_idt;

    __asm__("lidt %0" :: "m"(_idtr));
    __asm__("sti");
}

void idt_register_entry(uint16_t vect, volatile void* handler) {
    idt_desc_t* entry = &_idt[vect];

    entry->base_low  = (uint16_t)((uint32_t)handler & 0xFFFF);
    entry->base_high = (uint16_t)((uint32_t)handler >> 16);

    entry->segment = GDT_KCODE_SEG;
    entry->flags   = IDT_DEF_FLAGS;

    entry->reserved = 0;
}

void idt_isr_handler(uint8_t code) {
    char alert_s[47];
    str_cpy(alert_s, "Interrupt raised");

    if (code <= IDT_MESSAGES) {
        str_cat(alert_s, ": ");
        str_cat(alert_s, _isr_messages[code]);
    }

    sys_alert(alert_s, ALERT_ERR);
}

void idt_isr_overflow(uint8_t code) {
    sys_alert("Interrupt raised: Overflow", ALERT_WARN);
    __asm__("leave");
    __asm__("iret");
}