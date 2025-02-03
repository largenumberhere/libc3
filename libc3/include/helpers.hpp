#include "ints.hpp"
#include "mangled.hpp"


#ifdef __cplusplus
extern "C" {
#endif
    void libc3WriteStdout(const char* s);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
template <typename T> class Libc3RawArray {
private:
  T *_buff_start;
  size_t _buff_cap;

private:
  void boundsAssert(size_t pos);


public:
  // unsafe
  Libc3RawArray(T *buffer, size_t buffer_items_count);
  // unsafe
  Libc3RawArray(T *buffer, size_t buffer_items_count, bool zero);

  size_t len();

  T *getPtr(size_t index);
  T* getPtrSized(size_t index, size_t len);

  T get(size_t index);

  void setPtr(size_t index, T *value);

  void set(size_t index, T value);
};



template <typename T> class Libc3Array {
private:
  Libc3RawArray<T> _rawArray;
  size_t _len;

  void boundsAssert(size_t index);

public:
  // unsafe
  Libc3Array(T *buffer, size_t buffer_len);

  void push(T t);

  void pushPtrValue(T *t);

  T pop();

  T get(size_t index);

  void set(size_t index, T t);
};

#endif

#define TODO()  \
    libc3Exit(5);

#define UNREACHABLE()\
    libc3Exit(10);

#define PANIC()\
    libc3Exit(20);