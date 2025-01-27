#include "../../include/mangled.hpp"

extern "C" void libc3Exit(int exit_code) { libc3SysExit(exit_code); }