#include "../../include/libc3Mangled.hpp"
#include "../../include/libc3Ints.hpp"

void libc3TodoImpl(const char* filePath, size_t line, const char* message) {

    char line_string[32] = {0};
    libc3WriteStdout("Todo!\n    ");
    if (message[0] != '\0') {
        libc3WriteStdout("'");
        libc3WriteStdout(message);
        libc3WriteStdout("'");
        libc3WriteStdout("\n    ");
    }

    libc3WriteStdout(filePath);
    libc3WriteStdout(":");
    libc3IntegerToString(line, line_string);
    libc3WriteStdout(line_string);
    libc3WriteStdout("\n");

    libc3Exit(70);
}