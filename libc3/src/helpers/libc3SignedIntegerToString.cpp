#include "../../include/libc3Mangled.hpp"

// A buffer of at least 21 characters is needed. 
// Nul-terminator is added for you.
// returns the length of the characters used
extern "C" size_t libc3SignedIntegerToString(ssize_t val, char* buff_out) { 
    char * ptr = buff_out;
    bool negative = false;
    if (val < 0) {
      negative = true;
      val = -val;
      *ptr = '-';
      ptr++;
    }
  
    size_t len = libc3IntegerToString(val, ptr);
  
    if (negative) {
      len ++;
    }
  
    // ensure buffer is nul-terminated
    ptr[len] = '\0';
    
    return len;
}
  