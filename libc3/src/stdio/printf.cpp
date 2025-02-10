#include "../../include/ints.hpp"
#include "../../include/mangled.hpp"
#include "../../include/arrayWrapper.ipp"
#include "../../include/helpers.hpp"
#include <stdarg.h>


static void writeChar(char c) {
  char tmp[2] = {0};
  tmp[0] = c;
  libc3WriteStdout(tmp);
}


extern "C" size_t libc3PrintfA(const char *fmt, va_list *args) {
  size_t len = libc3Strlen(fmt);
  Libc3Array array = Libc3Array(fmt, len);


  // check if fmt contains %
  for (ssize_t i = 0; i < array.len(); i++) {
    char c = array.get(i);
    if (c == '%') {
      if (i+1 < array.len()) {
        char c2 = array.get(i+1);
        if (c2 == 'i') {

        } else if (c2 == 's') {

        } else if (c2 == 'c') {

        } else {
          UNIMPLEMENTED();
        }
      }
    } else {
      writeChar(c);
    }
  }

  return 1;
}
