#include "ints.hpp"
#include "mangled.hpp"

#ifdef cplusplus
extern "C" {
#endif

    size_t strlen(const char *string) { return libc3Strlen(string); }

    void _start();

#ifdef cplusplus
}
#endif
