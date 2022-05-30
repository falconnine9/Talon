#ifndef _KERNEL_H
#define _KERNEL_H 1

#define STACK_OFFSET  0x2200
#define KERNEL_OFFSET 0x2210
#define HEAP_OFFSET   0x100000
#define HEAP_MAX      0x8000000

void k_init();

#endif