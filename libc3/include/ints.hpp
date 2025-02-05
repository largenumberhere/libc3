#ifndef _LIBC3_INTS_H
#define _LIBC3_INTS_H
#include <stdbool.h>
#include <stddef.h>
// #include <stdint.h>

#include <stdint.h>
// #define NULL ((void*)0)

#define size_t unsigned long long

#ifndef __ssize_t
#define __ssize_t signed long long
#endif
typedef __ssize_t ssize_t; // stops collisions with glibc's definition

#endif