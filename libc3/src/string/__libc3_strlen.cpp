
#include "../../include/ints.hpp"

extern "C" size_t __libc3_strlen(const char *string) {
  size_t i = 0;

  const char *ptr = (const char *)string;

  while (ptr[i] != 0) {
    i++;
  }

  return i;
}