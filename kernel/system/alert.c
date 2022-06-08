#include <drivers/vga/vga.h>
#include <libc/types.h>

#include "sys.h"

static void        _alert_default(string_t msg, uint8_t level);
static sys_alert_t _alert_callback = _alert_default;

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
            attr = VGA_RED_LI;
            break;
        
        case ALERT_WARN:
            attr = VGA_YELLOW;
            break;
        
        case ALERT_INFO:
            attr = VGA_WHITE_LI;
            break;
        
        default:
            return;
    }
    sys_printcol("SYSTEM ALERT\n", attr);
    sys_printcol(msg, attr);
    sys_print("\n");
}