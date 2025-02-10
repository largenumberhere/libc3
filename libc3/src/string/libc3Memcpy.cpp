#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Mangled.hpp"

extern "C" void *libc3Memcpy(void *dest, const void * src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char*)dest)[i] = ((char*)src)[i];
    }

    return dest;
}
