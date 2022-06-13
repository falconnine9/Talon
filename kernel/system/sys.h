#ifndef _SYS_H
#define _SYS_H 1

#include <drivers/keyboard/keyboard.h>
#include <drivers/cpu/cpu.h>
#include <libc/libc.h>

typedef void(*sys_alert_t)(string_t, uint8_t);
typedef void(*sys_mask_t)();

#define ALERT_ERR  1
#define ALERT_WARN 2
#define ALERT_INFO 3

#define SYSCALL_VECT 0x40
#define SYSCALL_NUM  11

extern void syscall_isr();

void syscall_init();
void syscall_handler();

void sys_getkey(keypress_t* k);

void sys_putc(uint8_t x, uint8_t y, uint16_t c);
void sys_getvgacur(uint8_t* x, uint8_t* y);
void sys_setvgacur(uint8_t x, uint8_t y);

void sys_malloc(void* ptr, size_t size);
void sys_mfree(void* ptr);

void sys_getpit(uint32_t* tick);
void sys_getdatetime(datetime_t* dt);
void sys_setdatetime(datetime_t* dt);

void sys_alert(string_t msg, uint8_t level);
void sys_setalert(sys_alert_t callback);

#endif