#include "../../../include/ints.hpp"
#include "../../../include/mangled.hpp"
#include "../../../include/helpers.hpp"




struct fileHandleInner_s
{
    int fd;
    int flags;
};



class FileHandle {
    // required pre-conditions for this handle's implementation to be sound
    static_assert(alignof(Libc3File*) >= alignof(fileHandleInner_s));
    static_assert(sizeof(Libc3File*) == sizeof(fileHandleInner_s));

    private:
        fileHandleInner_s _inner;    
    public:
        explicit FileHandle(Libc3File* file_ptr) {
            struct fileHandleInner_s handle;
            libc3Memcpy(&handle, &file_ptr, sizeof(file_ptr));
            _inner = handle;
        };

        explicit FileHandle() : _inner({-1, 0}) {};

        explicit FileHandle(int fd) {
            fileHandleInner_s inner;
            inner.flags = -1;
            inner.fd = fd;

            _inner = inner;
        }

        Libc3File* intoPtr() {
            Libc3File* out; 
            libc3Memcpy(&out, &_inner, sizeof(out));

            return out;
        }

        int id() {
            return (int) _inner.fd;
        }
};
