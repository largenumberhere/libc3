#include "../libc3/include/libc3Mangled.hpp"
#include "util.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define KILOBYTE ((uint64_t)1000)
#define MEGABYTE ((uint64_t)1000000)
int main() {

  // warning: this can use 8 gigabytes for the backup allocator!
  for (int i = 0; i < 50; i++) {
    void *a = libc3Malloc(10);
    CHECK(a != NULL);
    memset(a, 0, 10);

    void *b = libc3Malloc(100);
    CHECK(b != NULL);
    memset(b, 0, 100);

    void *c = libc3Malloc(KILOBYTE);
    CHECK(c != NULL);
    memset(c, 0, KILOBYTE);

    void *d = libc3Malloc(MEGABYTE);
    CHECK(d != NULL);
    memset(d, 0, MEGABYTE);

    void *e = libc3Malloc(MEGABYTE * 100);
    CHECK(e != NULL);
    memset(e, 0, MEGABYTE * 100);

    // printf("%i %i %i %i %i", a, b, c, d, e);
    fprintf(stderr, "%p %p %p %p %p", a, b, c, d, e);

    libc3Free(a);
    libc3Free(b);
    libc3Free(c);
    libc3Free(d);
    libc3Free(e);
  }

  printf("ok");
  return 0;
}
