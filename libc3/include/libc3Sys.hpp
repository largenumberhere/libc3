#ifndef _LIBC3_SYS_H
#define _LIBC3_SYS_H
#include "libc3Ints.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void libc3SysExit(int exit_code);
void _start(); // entrypoint function on linux  // NOLINT(readability-identifier-naming)
size_t libc3SysWrite(int fd, const void *string, size_t len);
void *libc3SysHeapPageAlloc(void *hint, size_t bytes);
void libc3SysHeapPageFree(void *start, size_t bytes);
int libc3SysOpen(const char *pathname, int flags, int mode);
size_t libc3SysRead(int fd, char *buffer, size_t count);

#ifdef __cplusplus
}
#endif
#endif