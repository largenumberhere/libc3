#include "ints.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void libc3SysExit(int exit_code);
void _start();
size_t libc3SysWrite(int fd, const void *string, size_t len);

#ifdef __cplusplus
}
#endif
