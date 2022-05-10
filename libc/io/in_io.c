#include <drivers/keyboard/keyboard.h>
#include <libc/io.h>
#include <libc/types.h>

static char     _buffer[8 * 1024]; // 8KiB keyboard buffer
static uint16_t _buffer_i = 0;
static int16_t  _keycode  = -1;
static char     _keyc     = -1;
static bool_t   _rshifted  = FALSE;
static bool_t   _lshifted  = FALSE;

void _key_dispatch(uint8_t code);

char getc(bool_t catch) {
    kbd_set_waiting_key(_key_dispatch);

    while (_keyc == -1)
        __asm__("hlt");
    
    if (!catch)
        printc(_keyc);
    
    kbd_clear_waiting_key();
    return _keyc;
}

void gets(string_t dst, bool_t catch) {
    kbd_set_waiting_key(_key_dispatch);

    while (_keyc != '\n') {
        __asm__("hlt");
        _buffer[_buffer_i++] = _keyc;

        if (!catch)
            printc(_keyc);
    }

    if (!catch)
        printc('\n');
    
    for (int i = 0; i <= _buffer_i; i++)
        dst[i] = _buffer[i];
    
    _buffer_i = 0;
    kbd_clear_waiting_key();
}

void _key_dispatch(uint8_t code) {
    _keycode = code;
    _keyc    = kbd_get_key_char(code, _lshifted || _rshifted);

    if (_keyc == -1) {
        switch (code) {
            case KBD_LSHIFT_DOWN:
                _lshifted = TRUE;
                break;
            
            case KBD_LSHIFT_UP:
                _lshifted = FALSE;
                break;
            
            case KBD_RSHIFT_DOWN:
                _rshifted = TRUE;
                break;
            
            case KBD_RSHIFT_UP:
                _rshifted = FALSE;
                break;
        }
    }
}