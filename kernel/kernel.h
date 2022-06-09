#ifndef _KERNEL_H
#define _KERNEL_H 1

#include <libc/types.h>

#include "interrupts/interrupts.h"
#include "mm/memory.h"
#include "system/sys.h"

#define STACK_OFFSET  0x2200    // 8KiB stack area
#define KERNEL_OFFSET 0x2210    // ~400KiB kernel area
#define HEAP_OFFSET   0x100000  // Heap at 1MiB
#define HEAP_MAX      0x8000000 // 128MiB heap area

extern uint16_t k_memory;

void k_init();
void k_alert_entry();

#endif