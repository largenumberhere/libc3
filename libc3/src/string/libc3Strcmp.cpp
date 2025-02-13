#include "../../include/libc3ArrayWrapper.ipp"
#include "../../include/libc3Debug.hpp"
#include "../../include/libc3Mangled.hpp"

int libc3Strcmp(const char *s1, const char *s2) {
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

  // compare strings
  size_t i = 0;
  for (; true; i++) {
    if ((s1_arr.get(i) == '\0') || (s2_arr.get(i) == '\0') ||
        (s1_arr.get(i) != s2_arr.get(i))) {
      // return difference
      break;
    }
  }

  int difference = (int)s1_arr.get(i) - (int)s2_arr.get(i);
  // return difference;
  if (difference < 0) {
    return -1;
  } else if (difference == 0) {
    return 0;
  } else if (difference > 0) {
    return 1;
  }

  UNREACHABLE();
  return 0; // silence warning
}