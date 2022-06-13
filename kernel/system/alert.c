#include <drivers/vga/vga.h>
#include <libc/libc.h>

#include "sys.h"

static void        _alert_default(string_t msg, uint8_t level);
static sys_alert_t _alert_callback = _alert_default;

/*********************
 * System call masks *
 *********************/

void sysmask_alert() {
    uint32_t msg_ptr;
    uint8_t  level;
    __asm__("movl %%ebx, %0" : "=r"(msg_ptr));
    __asm__("mov %%cl, %0"   : "=r"(level));

    sys_alert((string_t)msg_ptr, level);
}

void sysmask_setalert() {
    uint32_t callback_ptr;
    __asm__("movl %%ebx, %0" : "=r"(callback_ptr));

    sys_setalert((sys_alert_t)callback_ptr);
}

/***********************
 * System call methods *
 ***********************/

void sys_alert(string_t msg, uint8_t level) {
    _alert_callback(msg, level);
}

void sys_setalert(sys_alert_t callback) {
    _alert_callback = callback;
}

static void _alert_default(string_t msg, uint8_t level) {
    uint8_t attr;
    switch (level) {
        case ALERT_ERR:
            attr = VGA_RED;
            break;
        
        case ALERT_WARN:
            attr = VGA_YELLOW;
            break;
        
        case ALERT_INFO:
            attr = VGA_WHITE;
            break;
        
        default:
            return;
    }
    printcol("Kernel: ", attr);
    printcol(msg, attr);
    print("\n");
}