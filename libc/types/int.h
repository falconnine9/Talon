#ifndef _LIBC_INT_H
#define _LIBC_INT_H 1

typedef signed char  int8_t;
typedef signed short int16_t;
typedef signed int   int32_t;

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

typedef unsigned int intptr_t;
typedef unsigned int uintptr_t;

typedef uint32_t size_t;

#define INT8_MAX  127
#define INT16_MAX 32767
#define INT32_MAX 2147483647

#define UINT8_MAX  255
#define UINT16_MAX 65535
#define UINT32_MAX 4294967295

size_t int_digits(int n);

#endif