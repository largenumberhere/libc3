#include "../../include/ints.hpp"
#include "../../include/mangled.hpp"
#include <stdarg.h>
size_t libc3PrintfA(char *fmt, va_list *args) {
    // check if fmt contains %
    for (size_t i = 0; i < libc3Strlen(fmt); i++) {
        if (fmt[i] == '%') {
            while (true) {}
        }
    }



    return 1;
}

