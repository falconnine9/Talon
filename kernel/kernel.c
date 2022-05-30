#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/types.h>

#include "kernel.h"
#include "interrupts/interrupts.h"
#include "mm/memory.h"

void k_main() {
    k_init();
    mm_init(HEAP_MAX, HEAP_OFFSET);

    for (int i = 0; i < 16; i++) {
        vga_draw_rect(VGA_POS(i * 20, 0), VGA_RECT(20, VGA_HEIGHT), i);
    }

    while (TRUE)
        __asm__("hlt");
}

void k_init() {
    pic_remap();
    pic_set_mask(0b11111111, 0);
    pic_set_mask(0b11111111, 1);

    idt_load_isrtable();
    kbd_init();
    pit_init();

    idt_set_register();
    pic_set_mask(0b11111101, 0);
}