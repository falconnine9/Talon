#ifndef _LIBC_SYS_H
#define _LIBC_SYS_H 1

#include <drivers/keyboard/keyboard.h>

#include "types.h"

void sys_sleep(uint32_t ms);
void sys_getkey(keypress_t* k);

#endif