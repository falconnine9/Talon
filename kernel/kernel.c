#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/types.h>

#include "kernel.h"

uint16_t k_memory;

void k_main(uint16_t mem_limit) {
    k_memory = mem_limit;
    
    k_init();
    mm_init(k_memory, HEAP_OFFSET);
    k_alert_entry();

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga_setattr(i % VGA_WIDTH, i / VGA_WIDTH, VGA_WHITE_LI);
}

void k_init() {
    pic_remap();
    pic_set_mask(0b11111111, 0);
    pic_set_mask(0b11111111, 1);

    idt_init();
    kbd_init();
    pit_init();

    pic_set_mask(0b11111100, 0);
    idt_set_register();
}

void k_alert_entry() {
    char mem_limit_s[7];
    str_fi(mem_limit_s, k_memory);
    sys_print("Kernel: ");
    sys_print(mem_limit_s);
    sys_print("KiB of memory detected");
}