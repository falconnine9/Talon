#ifndef _KERNEL_H
#define _KERNEL_H 1

#define STACK_OFFSET  0x2200
#define KERNEL_OFFSET 0x2210
#define HEAP_OFFSET   0xA010
#define HEAP_MAX      (HEAP_OFFSET + 0x8000000)

void k_init();

#endif