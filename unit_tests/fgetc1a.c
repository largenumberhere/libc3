#include "../libc3/include/mangled.hpp"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // write a file using glibc
  const char *file_path = ".temp.txt";
  FILE *f = fopen(file_path, "w");
  char *contents = "meow\nmeow\nmewowww";
  int count = fwrite(contents, strlen(contents), 1, f);
  fclose(f);

  // read the file back using libc3
  Libc3File *file = libc3Fopen(file_path, "r");
  for (int i = 0; i < strlen(contents); i++) {
    char c = (char)libc3Fgetc(file);
    CHECK(c == contents[i]);
  }

  CHECK(libc3Fgetc(file) == LIBC3_EOF);

  // delete temporary file
  remove(file_path);

  printf("ok");

  return 0;
}