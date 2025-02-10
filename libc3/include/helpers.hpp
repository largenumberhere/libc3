#ifndef LIBC3Helpers_H
#define LIBC3Helpers_H 1
#include "ints.hpp"
#include "mangled.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void libc3WriteStdout(const char *s);

#ifdef __cplusplus
}
#endif

#include "arrayWrapper.ipp"

void unimplementedImpl(const char* filePath, size_t line) {
    libc3WriteStdout("Unimplemented feature\n");
    libc3WriteStdout(filePath);
    libc3WriteStdout(":");
    char line_string[32] = {0};
    libc3IntegerToString(line, line_string);
    libc3WriteStdout(line_string);
    libc3WriteStdout("\n");

    libc3Exit(60);
}

#define UNIMPLEMENTED() \
    unimplementedImpl(__FILE__, __LINE__);

#endif