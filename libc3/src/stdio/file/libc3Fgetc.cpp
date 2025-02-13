#include "../../../include/libc3Ints.hpp"
#include "../../../include/libc3Mangled.hpp"
#include "../../../include/libc3Sys.hpp"
#include "libc3FileHandle.ipp"

int libc3Fgetc(Libc3File *stream) {
  FileHandle f = FileHandle(stream);
  int fd = f.id();

  char out = 0;

  size_t count = libc3SysRead(fd, &out, 1);
  if (count == 0) {
    return LIBC3_EOF;
  }

  return out;
}
