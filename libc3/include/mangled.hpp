// Expose the unmangled function names for testing purposes
#ifndef LIBC2_MANGLED
#define LIBC2_MANGLED
#include "ints.hpp"
#include "sys.hpp"
#include <stdarg.h>

#ifdef __cplusplus 
extern "C" {
#endif
    size_t libc3Strlen(const char *string);    //NOLINT(bugprone-reserved-identifier)
    size_t libc3PrintfA(const char *fmt, va_list *args);

#ifdef __cplusplus 
}
#endif

#endif