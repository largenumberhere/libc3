// Expose the unmangled function names for testing purposes
#ifndef _LIBC2_MANGLED
#define _LIBC2_MANGLED 1
#include "ints.hpp"

extern "C" size_t __libc3_strlen(const char *string);

#endif