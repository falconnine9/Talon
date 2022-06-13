#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H 1

#include <libc/def.h>
#include <libc/types.h>

typedef struct {
    uint16_t base_low;
    uint16_t segment;
    uint8_t  reserved;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed)) idt_desc_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_reg_t;

#define GDT_KCODE_SEG 0x8

#define IDT_SIZE      256
#define IDT_ISR_MAX   32
#define IDT_MESSAGES  19
#define IDT_DEF_FLAGS 0b10001110

void idt_init();
void idt_set_register();
void idt_register_entry(uint16_t vect, volatile void* handler);
void idt_isr_handler(uint8_t code);
void idt_isr_overflow(uint8_t code);

#endif