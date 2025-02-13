#ifndef LIBC3Helpers_H
#define LIBC3Helpers_H 1
#include "libc3Ints.hpp"
#include "libc3Mangled.hpp"

#ifdef __cplusplus
extern "C" {
#endif


enum LIBC3_DEBUG_EXIT_CODES {
    LIBC3_UNIMPLEMENTED_ERROR = 60,
    LIBC3_UNREACHABLE_ERROR = 70,
    LIBC3_TODO_ERROR = 80,
    LIBC3_PANIC_ERROR = 90,
};

#ifdef __cplusplus
}
#endif

#include "libc3ArrayWrapper.ipp"


#define UNIMPLEMENTED() libc3UnimplementedImpl(__FILE__, __LINE__);

#define UNREACHABLE() libc3UnreachableImpl(__FILE__, __LINE__);

#define TODO(...) libc3TodoImpl(__FILE__, __LINE__, __VA_ARGS__ "");

#define PANIC(...) libc3PanicImpl(__FILE__, __LINE__, __VA_ARGS__ "");

#endif