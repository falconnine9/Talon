#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/types.h>

#include "kernel.h"

uint16_t   k_memory;
datetime_t k_datetime;
gdt_tss_t* k_tss;

// The mem_limit and tss values are provided by the bootloader
void k_main(uint16_t mem_limit, volatile void* tss) {
    k_memory = mem_limit;
    k_tss    = (gdt_tss_t*)tss;
    
    k_init();
    mm_init(k_memory, HEAP_OFFSET);
    k_msg_memory();

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga_setattr(i % VGA_WIDTH, i / VGA_WIDTH, VGA_WHITE_LI);
}

void k_init() {
    pic_remap();
    pic_set_mask(0b11111111, 0);
    pic_set_mask(0b11111111, 1);
    k_message("PIC remapped and temporarily disabled");

    idt_init();
    k_message("ISRs placed in the IDT");

    kbd_init();
    k_message("Keyboard IRQ set");

    pit_init();
    rtc_init();
    k_message("RTC/PIT IRQ and frequency set");

    pic_set_mask(0b11111100, 0);
    idt_set_register();
}

void k_msg_memory() {
    char* mem_message_s = sys_malloc(35);

    str_cpy(mem_message_s, "Detected ");
    str_fi(mem_message_s + 9, k_memory);
    str_cat(mem_message_s, "KiB of memory");
    k_message(mem_message_s);

    sys_mfree(mem_message_s);
}