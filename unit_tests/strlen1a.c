#include "../libc3/include/libc3Mangled.hpp"
#include "util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  CHECK(libc3Strlen("mrow") == 4);
  CHECK(libc3Strlen("") == 0);
  CHECK(libc3Strlen("aaaaaaaaaaaaaaaaaaaa") == 20);

  printf("ok");
  return 0;
}
