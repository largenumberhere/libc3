#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Mangled.hpp"

// A buffer of at least 21 characters is needed. 
// Nul-terminator is added for you.
// returns the length of the characters used
extern "C" size_t libc3IntegerToString(size_t val, char *buff_out) {
	ssize_t buff_len = 0;

	if (val ==0) {
		buff_out[0] = '0';
    buff_len++;
    return buff_len;
	}
	
	size_t c = 0;
	char m = '\0';

	while (val > 0)
	{
		c = val % 10;
		val = val / 10;
		m = (char) '0' + c;
		buff_out[buff_len++] = m;
	}

  // reverese the array
  size_t left_cursor = 0;
  size_t right_cursor = buff_len-1;
  for (;  (left_cursor < buff_len/2); left_cursor++, right_cursor--)
  {
    char left = buff_out[left_cursor];
    buff_out[left_cursor] = buff_out[right_cursor];
    buff_out[right_cursor] = left;
  }
  
  // ensure buffer is nul-terminated
  buff_out[buff_len] = '\0';

  return buff_len;
}
