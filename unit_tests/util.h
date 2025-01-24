#define CHECK(condition)  \
  do {  \
  if (!(condition)) { \
    fprintf(stderr, "TEST FAILED %s:%d '%s'", __FILE__, __LINE__, #condition); \
    exit(1);\
  } \
  } while(0)