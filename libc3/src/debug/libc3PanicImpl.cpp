#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Mangled.hpp"

void libc3PanicImpl(int argCount, const char* filePath, size_t line, const char* message) {
    
        char line_string[32] = {0};
        libc3WriteStdout("Panic!\n    ");
        if (message !=NULL) {
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