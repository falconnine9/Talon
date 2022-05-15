#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/io.h>
#include <libc/sys.h>
#include <libc/types.h>

#include "kernel.h"
#include "interrupts/interrupts.h"

void k_main() {
    k_init();
    prints("Press enter to start text editor");

    keypress_t key;
    do {
        getkey(&key, TRUE);
    } while (key.c != '\n');
    
    editor_init();
    editor_start();

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
    pic_set_mask(0b11111100, 0);
}