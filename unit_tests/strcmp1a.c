#include "../libc3/include/libc3Mangled.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


int main() {
    // check for s1 < s2
    CHECK(
        libc3Strcmp("a", "b") == strcmp("a", "b")
    );

    // check for s1 == s2
    CHECK(
        libc3Strcmp("aaaa", "aaaa") == strcmp("aaaa", "aaaa")
    );

    // check for s1 < s2 for length 2
    CHECK(
        libc3Strcmp("ab", "ba") == strcmp("ab", "ba")
    );

    // check s2 > s2
    CHECK(
        libc3Strcmp("ba", "ab") == strcmp("ba", "ab")
    );

    // check different lengths
    CHECK(
        libc3Strcmp("ba", "abcd") == strcmp("ba", "abcd")
    );


    printf("ok");
    return 0;
}