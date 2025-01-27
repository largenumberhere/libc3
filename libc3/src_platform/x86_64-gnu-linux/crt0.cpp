#include "../../include/ints.hpp"
#include "../../include/sys.hpp"

extern "C" void _start() {
  __asm__(".extern main\n\t"
          "call main\n\t");

  libc3SysExit(0);
}