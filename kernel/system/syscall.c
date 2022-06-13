#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <kernel/kernel.h>
#include <libc/libc.h>

#include "sys.h"
#include "sys_masks.h"

static sys_mask_t _syscall_masks[SYSCALL_NUM] = {
    sysmask_getkey,      // 0x0

    sysmask_putc,        // 0x1
    sysmask_getvgacur,   // 0x2
    sysmask_setvgacur,   // 0x3

    sysmask_malloc,      // 0x4
    sysmask_mfree,       // 0x5

    sysmask_getpit,      // 0x6
    sysmask_getdatetime, // 0x7
    sysmask_setdatetime, // 0x8

    sysmask_alert,       // 0x9
    sysmask_setalert     // 0xA
};

void syscall_init() {
    idt_register_entry(SYSCALL_VECT, syscall_isr);
}

void syscall_handler() {
    uint16_t code;
    __asm__("mov %%ax, %0" : "=r"(code));

    _syscall_masks[code]();
}