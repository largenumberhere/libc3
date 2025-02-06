#include "../../include/sys.hpp"
#include "../../include/ints.hpp"

#define REGISTER uint64_t

enum REGISTER_VALUE { EMPTY = 0 };

// a naughty wrapper over C-style casting
template <typename T> constexpr static REGISTER registerCast(T t) {
  return (REGISTER)t;
}

// a naughty wrapper over C-style casting
template <typename T> constexpr static T registerUncast(REGISTER reg) {
  return (T)reg;
}

// take care not to switch the paramaters for this one, there is little type
// safety!
static REGISTER
libc3Syscall6(int id, REGISTER reg1, REGISTER reg2,
              REGISTER reg3, // NOLINT(bugprone-easily-swappable-parameters)
              size_t reg4, size_t reg5, size_t reg6) {
  volatile register size_t rax asm("rax") = (size_t)id;
  volatile register size_t rdi asm("rdi") = (size_t)reg1;
  volatile register size_t rsi asm("rsi") = (size_t)reg2;
  volatile register size_t rdx asm("rdx") = (size_t)reg3;
  volatile register size_t r10 asm("r10") = (size_t)reg4;
  volatile register size_t r8 asm("r8") = (size_t)reg5;
  volatile register size_t r9 asm("r9") = (size_t)reg6;

  asm volatile("syscall"
               : "+r"(rax)
               : "r"(rax), "r"(rdi), "r"(rsi), "r"(rdx), "r"(r10), "r"(r8),
                 "r"(r9)
               : "memory", "rcx", "r11");

  return rax;
}

static REGISTER libc3Syscall5(int id, REGISTER reg1, REGISTER reg2,
                              REGISTER reg3, REGISTER reg4, REGISTER reg5) {
  return libc3Syscall6(id, reg1, reg2, reg3, reg4, reg5, EMPTY);
}
static size_t libc3Syscall4(int id, REGISTER reg1, REGISTER reg2, REGISTER reg3,
                            REGISTER reg4) {
  return libc3Syscall6(id, reg1, reg2, reg3, reg4, EMPTY, EMPTY);
}

static size_t libc3Syscall3(int id, REGISTER reg1, REGISTER reg2,
                            REGISTER reg3) {
  return libc3Syscall6(id, reg1, reg2, reg3, EMPTY, EMPTY, EMPTY);
}

static size_t libc3Syscall2(int id, REGISTER reg1, REGISTER reg2) {
  return libc3Syscall6(id, reg1, reg2, EMPTY, EMPTY, EMPTY, EMPTY);
}

static size_t libc3Syscall1(int id, REGISTER reg1) {
  return libc3Syscall6(id, reg1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY);
}

static size_t libc3Syscall0(int id) {
  return libc3Syscall6(id, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY);
}

enum SYSCALLS {
  SYS_READ = 0,
  SYS_WRITE = 1,
  SYS_CLOSE = 3,
  SYS_BRK = 12,
  SYS_EXIT = 60,
  SYS_OPENAT = 257,
  SYS_MMAP = 9,
  SYS_MUNMAP = 11,
  SYS_PIPE = 22,
  SYS_KILL = 62,

};

extern "C" {
size_t libc3SysWrite(int fd, const void *string, size_t len) {
  size_t v = (size_t)libc3Syscall3(SYS_WRITE, fd, registerCast(string),
                                   registerCast(len));
  return v;
}

void libc3SysExit(int exit_code) {
  libc3Syscall1(SYS_EXIT, exit_code);

  while (1) {
  }
}

size_t libc3SysRead(int fd, char *buffer, size_t count) {
  return libc3Syscall3(SYS_READ, registerCast(fd), registerCast(buffer),
                       registerCast(count));
}

size_t libc3SysBrk(size_t brk) {
  size_t brk_val = libc3Syscall1(SYS_BRK, registerCast(brk));
  return (size_t)brk_val;
}

// https://sites.uclouvain.be/SystInfo/usr/include/linux/fcntl.h.html
enum OPEN_MODE { AT_FDCWD = -100 };
/* Special value used to indicate
  openat should use the current
  working directory. */

int libc3SysOpen(const char *pathname, int flags, int mode) {
  return (int)libc3Syscall4(SYS_OPENAT, AT_FDCWD, registerCast(pathname),
                            registerCast(flags), registerCast(mode));
}

void *libc3SysMmap(void *addr, unsigned long long length, int prot, int flags,
                   int fd, long offset) {
  void *ret = registerUncast<void *>(libc3Syscall6(
      SYS_MMAP, registerCast(addr), registerCast(length), registerCast(prot),
      registerCast(flags), registerCast(fd), registerCast(offset)));
  return ret;
}

int libc3SysMunmap(void *addr, size_t length) {
  return (int)libc3Syscall2(SYS_MUNMAP, registerCast(addr),
                            registerCast(length));
}

int libc3SysClose(int fd) {
  return (int)libc3Syscall1(SYS_CLOSE, registerCast(fd));
}

// file_des a pointer to 2 integers
int libc3SysPipe(int *file_des) {
  return (int)libc3Syscall1(SYS_PIPE, registerCast(file_des));
}

int libc3SysKill(int pid, int sig) {
  return (int)libc3Syscall2(SYS_KILL, registerCast(pid), registerCast(sig));
}

enum MMAP_PROTECTIONS {
  PROT_READ = 1,
  PROT_WRITE = 2,
  PROT_EXEC = 4,
};



enum MMAP_FLAGS {
  MAP_ANONYMOUS =32,
  MAP_PRIVATE = 2,
  MAP_SHARED = 1,
};

// returns NULL on failure
void* libc3SysHeapPageAlloc(void* hint, size_t bytes) {
  void* ptr = libc3SysMmap(hint, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
  if ((uint64_t)ptr == (uint64_t)-1) {
    return NULL;
  } 

  return ptr;
}
void libc3SysHeapPageFree(void* start, size_t bytes) {
  libc3SysMunmap(start, bytes);
}



}