#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Sys.hpp"

extern "C" void _start() {
  __asm__(".extern main\n\t"
          "call main\n\t");

  libc3SysExit(0);
}