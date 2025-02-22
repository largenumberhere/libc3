#ifndef _LIBC3_UNMANGLED_H
#define _LIBC3_UNMANGLED_H
#include "libc3Ints.hpp"
#include "libc3Mangled.hpp"
#include "stdarg.h"
#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char *string) { return libc3Strlen(string); }
int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  size_t out = libc3PrintfA(fmt, &ap);

  va_end(ap);

  return (int)out;
}
void _start();
void exit(int exit_code) { libc3Exit(exit_code); }

#ifdef __cplusplus
}
#endif
#endif