#ifndef _CPU_H
#define _CPU_H 1

#include <libc/types.h>

typedef struct {
    uint32_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} __attribute__((packed)) datetime_t;

typedef struct {
	uint32_t prev_tss;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomap_base;
} __attribute__((packed)) gdt_tss_t;

#define PORT_PIC1_CTRL 0x20
#define PORT_PIC1_DATA 0x21
#define PORT_PIC2_CTRL 0xA0
#define PORT_PIC2_DATA 0xA1

#define PORT_RTC_SECOND 0x0
#define PORT_RTC_MINUTE 0x2
#define PORT_RTC_HOUR   0x4
#define PORT_RTC_DAY    0x7
#define PORT_RTC_MONTH  0x8
#define PORT_RTC_YEAR   0x9

#define PORT_CMOS_CTRL 0x70
#define PORT_CMOS_DATA 0x71

#define PIC_ICW_INIT        0x11
#define PIC_ICW_LOW_OFFSET  0x20
#define PIC_ICW_HIGH_OFFSET 0x28
#define PIC_ICW_CASCADE1    0x4
#define PIC_ICW_CASCADE2    0x2
#define PIC_ICW_X86         0x1

#define PORT_PIT_CTRL    0x43
#define PORT_PIT_COUNTER 0x40

#define PIT_REAL_FREQ 1193182
#define PIT_INT_FREQ  1000
#define PIT_IRQ_VECT  0x20

#define RTC_IRQ_VECT 0x28

extern uint32_t pit_tick;
extern void     pit_irq();
extern void     rtc_irq();

uint8_t port_byte_in(uint16_t port);
void    port_byte_out(uint16_t port, uint8_t data);
void    port_io_wait();

void pic_remap();
void pic_send_eoi(uint8_t irq);
void pic_set_mask(uint8_t mask, uint8_t pic);

void pit_init();
void pit_irq_handler();

void rtc_init();
void rtc_read(datetime_t* dt);
void rtc_inc(datetime_t* dt);
void rtc_irq_handler();

#endif