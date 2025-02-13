#ifndef LIBC3ArrayWrapper
#define LIBC3ArrayWrapper 1

#include "libc3Ints.hpp"
#include "libc3Mangled.hpp"

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

  // unsafe
  Libc3RawArray();

  size_t len();

  T *getPtr(size_t index);
  T *getPtrSized(size_t index, size_t len);

  T get(size_t index);

  void setPtr(size_t index, T *value);

  void set(size_t index, T value);
};

template <typename T>
Libc3RawArray<T>::Libc3RawArray(T *buffer, size_t buffer_items_count)
    : _buff_cap(buffer_items_count), _buff_start(buffer) {

  // zero the buffer
  // libc3Memset(buffer, 0, buffer_items_count * sizeof(*buffer));
}

// Default constructor. Called when type is created without arguments.
// Uses an array of length 0
template <typename T> Libc3RawArray<T>::Libc3RawArray() {
  _buff_cap = 0;
  _buff_start = NULL;
}

template <typename T> void Libc3RawArray<T>::boundsAssert(size_t pos) {
  if (pos >= this->_buff_cap) {
    int stdout = 1;
    libc3WriteStdout("Libc3RawArray access was out of bounds");
    char tmp[64] = {0};
    libc3IntegerToString(pos, &(tmp[0]));
    libc3WriteStdout(&(tmp[0]));
    libc3Exit(1);
    // no return
  }

  return;
}

template <typename T>
Libc3RawArray<T>::Libc3RawArray(T *buffer, size_t buffer_items_count, bool zero)
    : _buff_cap(buffer_items_count), _buff_start(buffer) {

  // zero the buffer
  if (zero) {
    libc3Memset(buffer, 0, buffer_items_count * sizeof(*buffer));
  }
};

template <typename T> size_t Libc3RawArray<T>::len() { return this->_buff_cap; }

template <typename T> T *Libc3RawArray<T>::getPtr(size_t index) {
  boundsAssert(index);
  return &this->_buff_start[index];
}

template <typename T>
T *Libc3RawArray<T>::getPtrSized(size_t index, size_t len) {
  boundsAssert(index);
  boundsAssert(index + len);

  return &this->_buff_start[index];
}

template <typename T> T Libc3RawArray<T>::get(size_t index) {
  boundsAssert(index);
  return this->_buff_start[index];
}

template <typename T> void Libc3RawArray<T>::setPtr(size_t index, T *value) {
  boundsAssert(index);
  (this->_buff_start)[index] = *value;
}

template <typename T> void Libc3RawArray<T>::set(size_t index, T value) {
  boundsAssert(index);
  // this is dangerous, but unavoidable, it is needed to implement an array
  // wrapper
  (this->_buff_start)[index] =
      value; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

template <typename T> class Libc3Array {
private:
  Libc3RawArray<T> _rawArray;
  size_t _len;

  void boundsAssert(size_t index);

public:
  // unsafe
  explicit Libc3Array(T *buffer, size_t buffer_len);

  // unsafe
  Libc3Array();

  void push(T t);

  void pushPtrValue(T *t);

  T pop();

  T get(size_t index);

  size_t len(); 

  void set(size_t index, T t);
};

template <typename T> void Libc3Array<T>::boundsAssert(size_t index) {
  if (index > _len) {
    libc3WriteStdout("Libc3Array access was out of bounds");
    char arr[32];
    libc3IntegerToString(index, (char *)arr);
    libc3WriteStdout((char *)arr);

    libc3SysExit(1);
    // no return
  }
}

template <typename T>
Libc3Array<T>::Libc3Array(T *buffer, size_t buffer_len)
    : _len(buffer_len), _rawArray(buffer, buffer_len) {}

template <typename T> void Libc3Array<T>::push(T t) {

  // libc3DumpSizet(this->_len);
  _rawArray.set(this->_len, t);
  this->_len++;
}

template <typename T> void Libc3Array<T>::pushPtrValue(T *t) {
  boundsAssert(this->_len);
  _rawArray.setPtr(this->_len, t);
  this->_len++;
}

template <typename T> T Libc3Array<T>::pop() {
  this->_len--;
  T t = _rawArray.get(this->_len);
  return t;
}

template <typename T> T Libc3Array<T>::get(size_t index) {
  boundsAssert(index);
  T item = _rawArray.get(index);
  return item;
}

template <typename T> void Libc3Array<T>::set(size_t index, T t) {
  boundsAssert(index);
  if (index == this->_len) {
    this->_len++;
  }

  this->_rawArray.set(index, t);
}

// Default constructor. Called when type is created without arguments.
// Uses an array of length 0
template <typename T> Libc3Array<T>::Libc3Array() : _rawArray(), _len(0) {
  // TODO: what is this supposed to be used for?
  // _rawArray = Libc3RawArray();
}

template <typename T> size_t Libc3Array<T>::len() {
  return this->_len;
}

#endif



#endif