#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Helpers.hpp"

void libc3UnimplementedImpl(const char* filePath, size_t line) {
    libc3WriteStdout("Unimplemented feature\n");
    libc3WriteStdout(filePath);
    libc3WriteStdout(":");
    char line_string[32] = {0};
    libc3IntegerToString(line, line_string);
    libc3WriteStdout(line_string);
    libc3WriteStdout("\n");

    libc3Exit(60);
}