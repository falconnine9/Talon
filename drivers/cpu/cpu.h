#ifndef _CPU_H
#define _CPU_H 1

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

#define PORT_PIC1_CTRL 0x20
#define PORT_PIC1_DATA 0x21
#define PORT_PIC2_CTRL 0xA0
#define PORT_PIC2_DATA 0xA1

#define IDT_SIZE      256
#define IDT_ISR_MAX   32
#define IDT_MESSAGES  19
#define IDT_DEF_FLAGS 0b10001110

#define GDT_KCODE_SEG 0x8

uint8_t port_byte_in(uint16_t port);
void    port_byte_out(uint16_t port, uint8_t data);
void    port_io_wait();

void idt_set_register();
void idt_load_isrtable();
void idt_register_entry(uint16_t vect, volatile void* handler);
void idt_isr_handler(uint8_t code);
void idt_isr_overflow();

void    pic_remap();
void    pic_send_eoi();
uint8_t pic_read_ir();
uint8_t pic_read_is();

#endif