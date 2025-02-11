#include "../libc3/include/libc3Mangled.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


int main() {
    // check for parity to strcmp where n == max(strlen(a)+1, strlen(b)+1)
    
    // check for s1 < s2
    CHECK(
        (libc3Strncmp("a", "c", 2) < 0) && (strncmp("a", "c", 2) < 0)
    );

    // check for s1 == s2
    CHECK(
        libc3Strncmp("aaaa", "aaaa", 5) == strncmp("aaaa", "aaaa", 5)
    );

    // check for s1 < s2 for length 2
    CHECK(
        (libc3Strncmp("ab", "ca", 3) < 0) && (strncmp("ab", "ca", 3) < 0)
    );

    // check s2 > s2
    CHECK(
        (libc3Strncmp("ba", "ab", 3) > 0) && (strncmp("ba", "ab", 3) > 0)
    ); 

    // check different lengths
    CHECK(
        (libc3Strncmp("fa", "abcd", 5) > 0) && (strncmp("fa", "abcd", 5) > 0)
    );


    // modified snippet from https://cplusplus.com/reference/cstring/strncmp/
    char str[][5] = { "R2D2" , "C3PO" , "R2A6" };
    // Looking for R2 astromech droids...
    bool found = false;
    for (int n=0 ; n<3 ; n++) {
        if (strncmp (str[n],"R2xx",2) == 0)
        {
            found = true;
        }
    }
    CHECK(found);

    found = false;
    for (int n=0 ; n<3 ; n++) {
        if (libc3Strncmp (str[n],"R2xx",2) == 0)
        {
            found = true;
        }
    }
    CHECK(found);
    


    printf("ok");
    return 0;
}