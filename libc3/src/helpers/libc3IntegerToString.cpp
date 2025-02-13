#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Mangled.hpp"
#include "../../include/libc3ArrayWrapper.ipp"

// A buffer of at least 21 characters is needed.
// Nul-terminator is added for you.
// returns the length of the characters used
extern "C" size_t libc3IntegerToString(size_t val, char *buff_out) {
  // ssize_t buff_len = 0;
  const size_t base = 10;
  const char ascii_zero = ((char)'0'); 

  Libc3Array array = Libc3Array(buff_out, 21);

  if (val == 0) {
    array.push('0');
    return array.len();
  }

  char c = 0;
  char m = '\0';

  while (val > 0) {
    c = (char) (val % base);
    val = val / base;
    m = ascii_zero + (char)c;
    array.push(m);
  }

  // reverese the array
  size_t left_cursor = 0;
  size_t right_cursor = array.len() - 1;
  for (; (left_cursor < array.len() / 2); left_cursor++, right_cursor--) {
    char left = array.get(left_cursor);
    array.set(left_cursor, array.get(right_cursor));
    array.set(right_cursor, left);
  }

  array.push('\0');

  return array.len();
}
