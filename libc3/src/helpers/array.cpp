#include "../../include/ints.hpp"
#include "../../include/mangled.hpp"
#include "../../include/helpers.hpp"

 

template <typename T>
Libc3RawArray<T>::Libc3RawArray(T *buffer, size_t buffer_items_count) 
  : _buff_cap(buffer_items_count), _buff_start(buffer) {
  
  // zero the buffer
  libc3Memset(buffer, 0, buffer_items_count * sizeof(*buffer));
}

template <typename T>
void Libc3RawArray<T>::boundsAssert(size_t pos) {
  if (pos >= this->_buff_cap) {
    int stdout = 1;
    libc3WriteStdout("Libc3RawArray access was out of bounds");
    libc3Exit(1);
    // no return
  }

  return;
}

template <typename T>
  Libc3RawArray<T>:: Libc3RawArray(T *buffer, size_t buffer_items_count, bool zero)
      : _buff_cap(buffer_items_count), _buff_start(buffer) {

    // zero the buffer
    if (zero) {
      libc3Memset(buffer, 0, buffer_items_count * sizeof(*buffer));
    }
  }
  ;

template <typename T>
size_t Libc3RawArray<T>::len() { return this->_buff_cap; }

template <typename T>
T* Libc3RawArray<T>::getPtr(size_t index) {
  boundsAssert(index);
  return &this->_buff_start[index];
}

template <typename T>
T* Libc3RawArray<T>::getPtrSized(size_t index, size_t len) {
  boundsAssert(index);
  boundsAssert(index + len);

  return &this->_buff_start[index];
}

template <typename T>
T Libc3RawArray<T>::get(size_t index) {
  boundsAssert(index);
  return this->_buff_start[index];
}

template <typename T>
void Libc3RawArray<T>::setPtr(size_t index, T *value) {
  boundsAssert(index);
  (this->_buff_start)[index] = *value;
}

template <typename T>
void Libc3RawArray<T>::set(size_t index, T value) {
  boundsAssert(index);
  // this is dangerous, but unavoidable, it is needed to implement an array
  // wrapper
  (this->_buff_start)[index] =
      value; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}


template <typename T>
void Libc3Array<T>::boundsAssert(size_t index) {
      if (index > _len) {
      int stdout = 1;
      libc3WriteStdout("Libc3Array access was out of bounds");
    //   libc3DumpSizet(index);
      libc3SysExit(1);
      // no return
    }
}

template <typename T>
Libc3Array<T>::Libc3Array(T *buffer, size_t buffer_len)
      : _len(0), _rawArray(buffer, buffer_len) {}


template <typename T>
void Libc3Array<T>::push(T t) {

  // libc3DumpSizet(this->_len);
  _rawArray.set(this->_len, t);
  this->_len++;
}

template <typename T>
void Libc3Array<T>::pushPtrValue(T *t) {
  _rawArray.setPtr(t, this->_len);
  this->_len++;
}

template <typename T>
T Libc3Array<T>::pop() {
  this->_len--;
  T t = _rawArray.get(this->_len);
  return t;
}

template <typename T>
T Libc3Array<T>::get(size_t index) {
  boundsAssert(index);
  T item = this->_rawArray->get(index);
  return item;
}

template <typename T>
void Libc3Array<T>::set(size_t index, T t) {
  boundsAssert(index);
  if (index == this->_len) {
    this->_len++;
  }

  this->_rawArray.set(index, t);
}



// template <typename T> class Libc3Array {
// private:
//   Libc3RawArray<T> _rawArray;
//   size_t _len;

  // void boundsAssert(size_t index) {
  //   if (index > _len) {
  //     int stdout = 1;
  //     libc3WriteStdout("Libc3Array access was out of bounds");
  //   //   libc3DumpSizet(index);
  //     libc3SysExit(1);
  //     // no return
  //   }
  // }

// public:
  // unsafe
  // Libc3Array(T *buffer, size_t buffer_len)
  //     : _len(0), _rawArray(buffer, buffer_len) {}

  // void push(T t) {

  //   // libc3DumpSizet(this->_len);
  //   _rawArray.set(this->_len, t);
  //   this->_len++;
  // }

  // void pushPtrValue(T *t) {
  //   _rawArray.setPtr(t, this->_len);
  //   this->_len++;
  // }

  // T pop() {
  //   this->_len--;
  //   T t = _rawArray.get(this->_len);
  //   return t;
  // }

  // T get(size_t index) {
  //   boundsAssert(index);
  //   T item = this->_rawArray->get(index);
  //   return item;
  // }

  // void set(size_t index, T t) {
  //   boundsAssert(index);
  //   if (index == this->_len) {
  //     this->_len++;
  //   }

  //   this->_rawArray.set(index, t);
  // }
// };