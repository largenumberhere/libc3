#include "../../include/libc3Mangled.hpp"
#include "../../include/libc3Ints.hpp"

void libc3UnreachableImpl(const char* filePath, size_t line) {
    libc3WriteStdout("Unreachable code reached!\n");
    libc3WriteStdout(filePath);
    libc3WriteStdout(":");
    char line_string[32] = {0};
    libc3IntegerToString(line, line_string);
    libc3WriteStdout(line_string);
    libc3WriteStdout("\n");

    libc3Exit(70);
}