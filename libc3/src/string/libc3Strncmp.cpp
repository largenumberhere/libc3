#include "../../include/libc3ArrayWrapper.ipp"
#include "../../include/libc3Debug.hpp"
#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Mangled.hpp"

int libc3Strncmp(const char *s1, const char *s2, size_t n) {
  Libc3Array s1_arr = Libc3Array(s1, libc3Strlen(s1) + 1);
  Libc3Array s2_arr = Libc3Array(s2, libc3Strlen(s2) + 1);

  // check for null pointers. Not required but nice to have
  if ((s1 == NULL) && (s2 == NULL)) {
    return 0;
  } else if (s1 == NULL) {
    return s2_arr.get(0);
  } else if (s2 == NULL) {
    return s1_arr.get(0);
  }

  // move cursor to first difference in value
  ssize_t i = 0;
  for (; i < n - 1; i++) {
    if ((s1_arr.get(i) == '\0') || (s2_arr.get(i) == '\0') ||
        (s1_arr.get(i) != s2_arr.get(i))) {
      break;
    }
  }

  // return difference
  int difference = (int)s1_arr.get(i) - (int)s2_arr.get(i);
  if (difference < 0) {
    return -1;
  } else if (difference == 0) {
    return 0;
  } else if (difference > 0) {
    return 1;
  }

  UNREACHABLE();
  return 0; // silence error
}