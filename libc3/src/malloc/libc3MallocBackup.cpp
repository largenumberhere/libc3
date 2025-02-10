/*
    A primitive bump allocator. It's so simple it cannot fail, but it's super wasteful.
*/

#include "../../include/libc3Helpers.hpp"
#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Mangled.hpp"

#define GIGABYTE ((size_t)1024*1024*1024)

enum MALLOC_ERROR {
    ERROR = 30,
};
extern "C" void *libc3Malloc(size_t size) {
    void* alloc = libc3SysHeapPageAlloc(NULL, size);
    if (alloc == NULL) {
        libc3WriteStdout("Failed to allocate 4GB of memory\n");
        libc3Exit(ERROR);
    }


    return alloc;

}
extern "C" void libc3Free(void *ptr) {
    return;

}