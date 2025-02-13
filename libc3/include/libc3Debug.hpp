#ifndef LIBC3Helpers_H
#define LIBC3Helpers_H 1
#include "libc3Ints.hpp"
#include "libc3Mangled.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#include "libc3ArrayWrapper.ipp"



#define UNIMPLEMENTED() \
    libc3UnimplementedImpl(__FILE__, __LINE__);

#define UNREACHABLE() \
    libc3UnreachableImpl(__FILE__, __LINE__);

#define TODO(...) \
    libc3TodoImpl(__FILE__, __LINE__, __VA_ARGS__ "");

#define PANIC(...) \
    libc3PanicImpl( __FILE__, __LINE__, __VA_ARGS__ "");\
    
#endif