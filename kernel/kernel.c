#include <drivers/cpu/cpu.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <libc/libc.h>

#include "kernel.h"

uint32_t   k_ml;
datetime_t k_dt;

// The mem_limit and heap_start values are provided by the bootloader
void k_main(uint32_t ml) {
    k_ml = ml;
    k_init();
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

    mm_init();
    sys_alert("Paging ready", ALERT_INFO);

    pic_set_mask(0b11111100, 0);
    idt_set_register();
    sys_alert("IDT register set and PIC enabled", ALERT_INFO);
}