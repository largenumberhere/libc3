// Expose the unmangled function names for testing purposes
#ifndef LIBC2_MANGLED
#define LIBC2_MANGLED
#include "ints.hpp"
#include "sys.hpp"  // platform specific internals
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif
size_t libc3Strlen(const char *string); // NOLINT(bugprone-reserved-identifier)
size_t libc3PrintfA(const char *fmt, va_list *args);
void libc3Exit(int exit_code);
void *libc3Malloc(size_t size);
void libc3Free(void *ptr);

// string.h
void *libc3Memset(void *s, int c, size_t n);
void *libc3Memcpy(void *dest, const void * src, size_t n);

// some internals
void libc3WriteStdout(const char *s);
void libc3IntegerToString(size_t value, char *out);

// file
typedef struct
{
    char _padding[64];
} Libc3File;

#define LIBC3_EOF ((int)-1)
int libc3Fgetc(Libc3File* stream);
Libc3File *libc3Fopen(const char * pathname, const char * mode);


#ifdef __cplusplus
}
#endif

#endif