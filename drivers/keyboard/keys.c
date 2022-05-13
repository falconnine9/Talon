#include <libc/types.h>

#include "keyboard.h"

// Arranged in rows as a physical keyboard would be
static uint8_t key_codes[KBD_CODE_SIZE] = {
    29, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 43,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 28,
    44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
    57
};

static char key_chars_low[KBD_CODE_SIZE] = {
    '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\n',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    ' '
};

static char key_chars_high[KBD_CODE_SIZE] = {
    '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '|',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '\n',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    ' '
};

char kbd_get_key_char(uint8_t code, bool_t shifted) {
    for (int i = 0; i < KBD_CODE_SIZE; i++) {
        if (key_codes[i] == code)
            return shifted ? key_chars_high[i] : key_chars_low[i];
    }

    return 0;
}