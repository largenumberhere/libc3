#include "../libc3/include/libc3Mangled.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


int main() {
     // check for s1 < s2
     CHECK(
        (libc3Strcmp("a", "c") < 0) && (strcmp("a", "c") < 0)
    );

    // check for s1 == s2
    CHECK(
        libc3Strcmp("aaaa", "aaaa") == strcmp("aaaa", "aaaa")
    );

    // check for s1 < s2 for length 2
    CHECK(
        (libc3Strcmp("ab", "ca") < 0) && (strcmp("ab", "ca") < 0)
    );

    // check s2 > s2
    CHECK(
        (libc3Strcmp("ba", "ab") > 0) && (strcmp("ba", "ab") > 0)
    ); 

    // check different lengths
    CHECK(
        (libc3Strcmp("fa", "abcd") > 0) && (strcmp("fa", "abcd") > 0)
    );




    printf("ok");
    return 0;
}