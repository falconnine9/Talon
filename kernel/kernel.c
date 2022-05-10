#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/io.h>
#include <libc/types.h>

#include "kernel.h"

void k_main() {
    k_init();
    prints("Hello world\n");
}

void k_init() {
    pic_remap();
    idt_load_isrtable();
    kbd_init();

    idt_set_register();
}