#ifndef _CPU_H
#define _CPU_H 1

#include <libc/types.h>

#define PORT_PIC1_CTRL 0x20
#define PORT_PIC1_DATA 0x21
#define PORT_PIC2_CTRL 0xA0
#define PORT_PIC2_DATA 0xA1

#define PIC_ICW_INIT        0x11
#define PIC_ICW_LOW_OFFSET  0x20
#define PIC_ICW_HIGH_OFFSET 0x28
#define PIC_ICW_CASCADE1    0x4
#define PIC_ICW_CASCADE2    0x2
#define PIC_ICW_X86         0x1

#define PORT_PIT_CTRL    0x43
#define PORT_PIT_COUNTER 0x40

#define PIT_FREQUENCY    1000
#define PIT_IRQ_VECT     0x20
#define PIT_INTERVAL_LEN 1000

uint8_t port_byte_in(uint16_t port);
void    port_byte_out(uint16_t port, uint8_t data);
void    port_io_wait();

void    pic_remap();
void    pic_send_eoi(uint8_t irq);
void    pic_set_mask(uint8_t mask, uint8_t pic);
void    pic_set_mask_line(uint8_t irq);
void    pic_clear_mask_line(uint8_t irq);
uint8_t pic_read_ir();
uint8_t pic_read_is();

void     pit_init();
void     pit_irq();
uint32_t pit_get_tick();

#endif