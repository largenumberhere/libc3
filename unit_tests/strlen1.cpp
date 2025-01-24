#include "../libc3/include/mangled.hpp"

#include <assert.h>
#include <iostream>
int main() {
  assert(__libc3_strlen("mrow") == 4);
  assert(__libc3_strlen("") == 0);
  assert(__libc3_strlen("aaaaaaaaaaaaaaaaaaaa") == 20);
}
