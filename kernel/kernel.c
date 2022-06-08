#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/types.h>

#include "kernel.h"

void k_main() {
    k_init();
    mm_init(HEAP_MAX, HEAP_OFFSET);

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