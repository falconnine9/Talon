#include <libc/libc.h>

#include "int.h"

size_t int_digits(int n) {
    int len = 1;
    while ((n /= 10) > 0)
        len++;
    return len;
}