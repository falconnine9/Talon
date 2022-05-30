#include <drivers/keyboard/keyboard.h>
#include <libc/sys.h>
#include <libc/types.h>

static keypress_t _key;
static void       _key_callback(uint16_t code);

void sys_getkey(keypress_t* k) {
    kbd_swk(_key_callback);
    
    while (_key.code == 0 || _key.code == 0xE0)
        __asm__("hlt");
    
    *k = _key;
    kbd_cwk();
}

static void _key_callback(uint16_t code) {
    if (_key.code == 0xE0) {
        _key.code <<= 8;
        _key.code |= code;
        return;
    }

    _key.code = code;
    if (code == 0xE0)
        return;
    
    _key.up = code >= 0x81;
    if (_key.up)
        _key.code -= 0x81;
}

