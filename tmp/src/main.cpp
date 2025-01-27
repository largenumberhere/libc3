#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef size_t

#define size_t unsigned long long // NOLINT(readability-identifier-naming)
#endif

#ifndef NULL
#define NULL (void *)0
#endif

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

void libc3SysExit(int status) {
  libc3Syscall1(60, status);

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

size_t libc3Strlen(const char *str) {
  for (size_t i = 0; true; i++) {
    if (str[i] == '\0') {
      return i;
    }
  }
}

void* libc3Memset(void *s, int c, size_t n) {
  for (size_t i = 0; i < n; i++) {
    *((char*) s) = (char)c;  
  }
  return s;
}


void libc3WriteStdout(const char *value) {
  int stdout = 1;
  libc3SysWrite(stdout, value, libc3Strlen(value));
}

void libc3PutsLen(const char *value, size_t len) {
  int stdout = 1;
  libc3SysWrite(stdout, value, len);
}

void libc3DumpSizet(size_t value) {
  libc3PutsLen((char *)(&value), sizeof(size_t));
}

void libc3DumpInt(int value) { libc3PutsLen((char *)(&value), sizeof(int)); }

template <typename T> class Libc3RawArray {
private:
  T *_buff_start;
  size_t _buff_cap;

private:
  void boundsAssert(size_t pos) {
    if (pos >= this->_buff_cap) {
      int stdout = 1;
      libc3WriteStdout("Libc3RawArray access was out of bounds");
      libc3SysExit(1);
      // no return
    }

    return;
  }

public:
  // unsafe
  Libc3RawArray(T *buffer, size_t buffer_items_count)
      : _buff_cap(buffer_items_count), _buff_start(buffer) {

    // zero the buffer
    libc3Memset(buffer, 0, buffer_items_count * sizeof(*buffer));
  }

  size_t len() { return this->_buff_cap; }

  T *getPtr(size_t index) {
    boundsAssert(index);
    return &this->_buff_start[index];
  }

  T get(size_t index) {
    boundsAssert(index);
    return this->_buff_start[index];
  }

  void setPtr(size_t index, T *value) {
    boundsAssert(index);
    (this->_buff_start)[index] = *value;
  }

  void set(size_t index, T value) {
    boundsAssert(index);
    // this is dangerous, but unavoidable, it is needed to implement an array wrapper
    (this->_buff_start)[index] = value; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) 
  }
};

template <typename T> class Libc3Array {
private:
  Libc3RawArray<T> _rawArray;
  size_t _len;

  void boundsAssert(size_t index) {
    if (index > _len) {
      int stdout = 1;
      libc3WriteStdout("Libc3Array access was out of bounds");
      libc3DumpSizet(index);
      libc3SysExit(1);
      // no return
    }
  }

public:
  // unsafe
  Libc3Array(T *buffer, size_t buffer_len)
      : _len(0), _rawArray(buffer, buffer_len) {}

  void push(T t) {

    libc3DumpSizet(this->_len);
    _rawArray.set(this->_len, t);
    this->_len++;
  }

  void pushPtrValue(T *t) {
    _rawArray.setPtr(t, this->_len);
    this->_len++;
  }

  T pop() {
    this->_len--;
    T t = _rawArray.get(this->_len);
    return t;
  }

  T get(size_t index) {
    boundsAssert(index);
    T item = this->_rawArray->get(index);
    return item;
  }

  void set(size_t index, T t) {
    boundsAssert(index);
    if (index == this->_len) {
      this->_len++;
    }

    this->_rawArray.set(index, t);
  }
};

extern "C" int _start() { // NOLINT(readability-identifier-naming)
  int one = 1;
  libc3DumpInt(111);

  int stdout = 1;

  char str[] = "hello, world!\n";
  libc3SysWrite(1, (char *)str, sizeof(str));

  char c_array[16] = {0};
  Libc3Array array = Libc3Array<char>((char *)c_array, sizeof(c_array));

  for (int i = 0; i < sizeof(c_array); i++) {
    array.push('a');
  }

  libc3SysWrite(stdout, (char *)c_array, sizeof(c_array));

  libc3SysExit(0);
  while (true) {
  }
}
