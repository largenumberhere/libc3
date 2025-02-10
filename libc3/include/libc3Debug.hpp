#ifndef LIBC3Helpers_H
#define LIBC3Helpers_H 1
#include "libc3Ints.hpp"
#include "libc3Mangled.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#include "libc3ArrayWrapper.ipp"

void libc3UnimplementedImpl(const char* filePath, size_t line);


#define UNIMPLEMENTED() \
    libc3UnimplementedImpl(__FILE__, __LINE__);

#endif