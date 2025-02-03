#include "../../include/ints.hpp"
#include "../../include/mangled.hpp"
#include "../../include/helpers.hpp"

 




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