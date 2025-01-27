#include "../../include/sys.hpp"
#include "../../include/ints.hpp"

enum REGISTER_VALUE { EMPTY = 0 };

static size_t libc3Syscall6(int id, size_t reg1, size_t reg2, size_t reg3,
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

static size_t libc3Syscall2(int id, size_t reg1, size_t reg2) {
  return libc3Syscall6(id, reg1, reg2, EMPTY, EMPTY, EMPTY, EMPTY);
}

static size_t libc3Syscall1(int id, size_t reg1) {
  return libc3Syscall6(id, reg1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY);
}

static size_t libc3Syscall3(int id, size_t reg1, size_t reg2, size_t reg3) {
  return libc3Syscall6(id, reg1, reg2, reg3, EMPTY, EMPTY, EMPTY);
}

static size_t libc3Syscall4(int id, size_t reg1, size_t reg2, size_t reg3,
                            size_t reg4) {
  return libc3Syscall6(id, reg1, reg2, reg3, reg4, EMPTY, EMPTY);
}

size_t libc3SysWrite(int fd, const void *string, size_t len) {
  size_t v = libc3Syscall3(1, fd, (size_t)string, (size_t)len);
  return v;
}

extern "C" void libc3SysExit(int exit_code) {
  libc3Syscall1(60, exit_code);

  while (1) {
  }
}

size_t libc3SysRead(int fd, char *buffer, size_t count) {
  return libc3Syscall3(0, (size_t)fd, (size_t)buffer, (size_t)count);
}

size_t libc3SysBrk(size_t brk) {
  size_t brk_val = libc3Syscall1((size_t)12, (size_t)brk);
  return (size_t)brk_val;
}

// https://sites.uclouvain.be/SystInfo/usr/include/linux/fcntl.h.html
enum OPEN_MODE { AT_FDCWD = -100 };
/* Special value used to indicate
  openat should use the current
  working directory. */

int sys_open(const char *pathname, int flags, int mode) {
  return (int)libc3Syscall4(257, AT_FDCWD, (size_t)pathname, flags, mode);
}

void *sys_mmap(void *addr, unsigned long long length, int prot, int flags,
               int fd, long offset) {
  void *ret =
      (void *)libc3Syscall6(9, (size_t)addr, (size_t)length, (size_t)prot,
                            (size_t)flags, (size_t)fd, (size_t)offset);
  return ret;
}

int sys_munmap(void *addr, size_t length) {
  return (int)libc3Syscall2(11, (size_t)addr, (size_t)length);
}

int sys_close(int fd) { return libc3Syscall1(3, fd); }

// file_des a pointer to 2 integers
int libc3SysPipe(int *file_des) {
  return (int)libc3Syscall1(0x16, (size_t)file_des);
}

int libc3SysKill(int pid, int sig) {
  return libc3Syscall2(62, (size_t)pid, (size_t)sig);
}


