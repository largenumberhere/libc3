#include "../../include/ints.hpp"

extern "C" void *libc3Memset(void *s, int c, size_t n) {
  for (ssize_t i = 0; i < n; i++) {
    ((char *)s)[i] = (char)c;
  }

  return s;

  // char c2 = (char) c;
  // char* s2 = (char*)s;
  // for (size_t i = 0; i < n; i++) {
  //     s2[i] = c2;
  // }
}