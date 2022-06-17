#ifndef _KERNEL_H
#define _KERNEL_H 1

#include <drivers/cpu/cpu.h>
#include <libc/libc.h>

#include "interrupts/interrupts.h"
#include "mm/memory.h"
#include "system/sys.h"

#define STACK_OFFSET  0x2200
#define KERNEL_OFFSET 0x2210

extern uint32_t   k_ml;
extern datetime_t k_dt;

void k_main(uint32_t ml);
void k_init();

#endif