#include "../../../include/libc3Ints.hpp"
#include "../../../include/libc3Sys.hpp"
#include "libc3FileHandle.ipp"
#include "../../../include/libc3Mangled.hpp"

Libc3File *libc3Fopen(const char *pathname,
                      const char *mode) // NOLINT(bugprone-easily-swappable-parameters)
                                        // - builtin function
{
  const int O_CREAT = 0100;
  const int O_WRONLY = 01;

  if (libc3Strlen(mode) > 1) {
    UNIMPLEMENTED();
  }

  if (mode[0] == 'r') {
    int fd = libc3SysOpen(pathname, 0, 0700);
    if (fd == -1) {
      UNIMPLEMENTED();
    }

    FileHandle handle = FileHandle(fd);
    return handle.intoPtr();

  } else {
    UNIMPLEMENTED();
  }

  UNIMPLEMENTED();
  FileHandle default_handle = FileHandle();
  return default_handle.intoPtr();
};

