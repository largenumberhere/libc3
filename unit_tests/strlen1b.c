#include "../libc3/include/unmangled.hpp"
#include "util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  CHECK(strlen("mrow") == 4);
  CHECK(strlen("") == 0);
  CHECK(strlen("aaaaaaaaaaaaaaaaaaaa") == 20);
  
  printf("ok");
  return 0;
}
