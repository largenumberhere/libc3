#include "ints.hpp"
#include "mangled.hpp"
#include "stdarg.h"
#ifdef __cplusplus
extern "C" {
#endif

    size_t strlen(const char *string) { return libc3Strlen(string); }
    int printf(const char *fmt, ...) {
        va_list ap;
        va_start(ap ,fmt);

        size_t out = libc3PrintfA(fmt, &ap);

        va_end(ap);

        return  (int)out;

    }
    void _start();
    void exit(int exit_code) {
        libc3Exit(exit_code);
    }

#ifdef __cplusplus
}
#endif
