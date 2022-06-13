#ifndef _LIBC_H
#define _LIBC_H 1

// Type declarations for more specification
#include "types/bool.h"
#include "types/int.h"
#include "types/string.h"

#define NULL 0

void* malloc(size_t size);
void  free(void* ptr);
void  print(string_t msg);
void  printcol(string_t msg, uint8_t attr);
void  sleep(uint32_t ms);

#endif