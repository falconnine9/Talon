#ifndef _SYS_H
#define _SYS_H 1

#include <drivers/keyboard/keyboard.h>
#include <libc/types.h>

typedef void(*sys_alert_t)(string_t, uint8_t);

#define ALERT_ERR  1
#define ALERT_WARN 2
#define ALERT_INFO 3

void sys_getkey(keypress_t* k);
void sys_print(string_t msg);
void sys_printcol(string_t msg, uint8_t attr);

void* sys_malloc(size_t size);
void  sys_mfree(void* ptr);

void sys_sleep(uint32_t ms);

void sys_alert(string_t msg, uint8_t level);

#endif