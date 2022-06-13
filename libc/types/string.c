#include <libc/libc.h>

#include "string.h"

size_t str_len(string_t str) {
    size_t len = 0;
    while (*str++ != '\0')
        len++;
    return len;
}

void str_cat(string_t dst, string_t src) {
    dst += str_len(dst);
    str_cpy(dst, src);
}

void str_cpy(string_t dst, string_t src) {
    char c;
    do {
        c      = *src++;
        *dst++ = c;
    } while (c != '\0');
}

void str_fi(string_t str, int n) {
    int sign = n < 0;
    str     += int_digits(n) + sign;
    *str--   = '\0';

    do {
        *str-- = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign == 1)
        *str = '-';
}

int str_ti(string_t str) {
    int multi  = 1;
    int result = 0;
    
    for (int i = str_len(str) - 1; i >= 0; i--) {
        result += (str[i] - '0') * multi;
        multi  *= 10;
    }

    return result;
}