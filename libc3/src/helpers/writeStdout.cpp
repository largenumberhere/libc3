#include "../../include/mangled.hpp"
#include "../../include/sys.hpp"

extern "C" void libc3WriteStdout(const char* s) {
    const int stdout = 1;
    size_t len = libc3Strlen(s);
    libc3SysWrite(stdout, s, len);
}