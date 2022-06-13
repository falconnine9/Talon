#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/libc.h>

#include "kernel.h"

uint16_t   k_memory;
datetime_t k_datetime;

// The mem_limit and tss values are provided by the bootloader
void k_main(uint16_t mem_limit) {
    k_memory = mem_limit;
    
    k_init();
    mm_init(k_memory, HEAP_OFFSET);
    sys_alert("Heap initialized after 1MiB", ALERT_INFO);
}

void k_init() {
    pic_remap();
    pic_set_mask(0b11111111, 0);
    pic_set_mask(0b11111111, 1);
    sys_alert("PIC remapped and temporarily disabled", ALERT_INFO);

    idt_init();
    sys_alert("ISRs placed in the IDT", ALERT_INFO);

    kbd_init();
    sys_alert("Keyboard IRQ set", ALERT_INFO);

    pit_init();
    rtc_init();
    sys_alert("RTC/PIT IRQ and frequency set", ALERT_INFO);

    syscall_init();
    sys_alert("System calls ready", ALERT_INFO);

    pic_set_mask(0b11111100, 0);
    idt_set_register();
}