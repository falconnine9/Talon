#include <drivers/keyboard/keyboard.h>
#include <libc/io.h>
#include <libc/types.h>

static char     _buffer[8 * 1024]; // 8KiB keyboard buffer
static uint16_t _buffer_i = 0;

static keypress_t _keypress;
static bool_t     _rshifted = FALSE;
static bool_t     _lshifted = FALSE;
static bool_t     _alt      = FALSE;
static bool_t     _ctrl     = FALSE;

static void _key_callback(uint8_t code);
static void _clear_keypress();

char getc() {
    kbd_set_waiting_key(_key_callback);

    while (_keypress.c == '\0')
        __asm__("hlt");
    
    char key = _keypress.c;
    _clear_keypress();

    kbd_clear_waiting_key();
    return key;
}

void gets(string_t dst) {
    kbd_set_waiting_key(_key_callback);
    _buffer_i = 0;

    while (TRUE) {
        __asm__("hlt");

        if (_keypress.c == 0)
            continue;

        if (_keypress.c == '\n')
            break;
        
        _buffer[_buffer_i++] = _keypress.c;
        printc(_keypress.c);
        _clear_keypress();
    }
    printc('\n');
    
    for (int i = 0; i <= _buffer_i; i++)
        dst[i] = _buffer[i];
    
    kbd_clear_waiting_key();
}

void getkey(keypress_t* dst, bool_t catch) {
    kbd_set_waiting_key(_key_callback);

    while (_keypress.c == '\0')
        __asm__("hlt");
    
    dst->code    = _keypress.code;
    dst->c       = _keypress.c;
    dst->shifted = _lshifted || _rshifted;
    dst->alt     = _alt;
    dst->ctrl    = _ctrl;
    _clear_keypress();

    kbd_clear_waiting_key();
}

static void _key_callback(uint8_t code) {
    if (code < 129) {
        _keypress.code = code;
        _keypress.c    = kbd_get_key_char(code, _lshifted || _rshifted);
    }

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
            
        case KBD_ALT_DOWN:
            _alt = TRUE;
            break;
            
        case KBD_ALT_UP:
            _alt = FALSE;
            break;
            
        case KBD_CTRL_DOWN:
            _ctrl = TRUE;
            break;
            
        case KBD_CTRL_UP:
            _ctrl = FALSE;
            break;
    }
}

static void _clear_keypress() {
    _keypress.code    = 0;
    _keypress.c       = 0;
}