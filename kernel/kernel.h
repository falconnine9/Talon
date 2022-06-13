#ifndef _KERNEL_H
#define _KERNEL_H 1

#include <drivers/cpu/cpu.h>
#include <libc/libc.h>

#include "interrupts/interrupts.h"
#include "mm/memory.h"
#include "system/sys.h"

#define STACK_OFFSET  0x2200    // 8KiB stack area
#define KERNEL_OFFSET 0x2210    // ~400KiB kernel area
#define HEAP_OFFSET   0x100000  // Heap start at 1MiB

extern uint16_t   k_memory;
extern datetime_t k_datetime;

void k_main(uint16_t mem_limit);
void k_init();

#endif