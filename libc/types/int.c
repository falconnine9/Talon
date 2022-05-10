#include "int.h"

size_t int_digits(int n) {
    int len = 0;
    while ((n /= 10) > 0)
        len++;
    return len;
}