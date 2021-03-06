#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H 1

#include <libc/libc.h>

#include "string.h"

typedef char* string_t;

// String utility functions
size_t str_len(string_t str);
void   str_cat(string_t dst, string_t src);
void   str_cpy(string_t dst, string_t src);

// String conversion functions
void str_fi(string_t str, int n);
int  str_ti(string_t str);

#endif