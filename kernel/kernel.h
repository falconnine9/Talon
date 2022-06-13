#ifndef _KERNEL_H
#define _KERNEL_H 1

#include <drivers/cpu/cpu.h>
#include <libc/types.h>

#include "interrupts/interrupts.h"
#include "mm/memory.h"
#include "system/sys.h"

#define STACK_OFFSET  0x2200    // 8KiB stack area
#define KERNEL_OFFSET 0x2210    // ~400KiB kernel area
#define HEAP_OFFSET   0x100000  // Heap start at 1MiB

extern uint16_t   k_memory;
extern datetime_t k_datetime;
extern gdt_tss_t* k_tss;

void k_init();
void k_msg_memory();
void k_message();
void k_message_err();

#endif