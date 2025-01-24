// Expose the unmangled function names for testing purposes
#ifndef LIBC2_MANGLED
#define LIBC2_MANGLED
#include "ints.hpp"

#ifdef cplusplus 
extern "C" {
#endif
    size_t libc3Strlen(const char *string);    //NOLINT(bugprone-reserved-identifier)


#ifdef cplusplus 
}
#endif

#endif