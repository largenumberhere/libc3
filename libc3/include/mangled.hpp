// Expose the unmangled function names for testing purposes
#ifndef LIBC2_MANGLED
#define LIBC2_MANGLED
#include "ints.hpp"
#include "sys.hpp"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif
size_t libc3Strlen(const char *string); // NOLINT(bugprone-reserved-identifier)
size_t libc3PrintfA(const char *fmt, va_list *args);
void libc3Exit(int exit_code);
void *libc3Malloc(size_t size);
void libc3Free(void* ptr);

// internals
void libc3WriteStdout(const char* s);

#ifdef __cplusplus
}
#endif

#endif