#define FILE void
#include "../../include/ints.hpp"
#include "../../include/sys.hpp"


FILE *fopen(const char * pathname, const char * mode)   //NOLINT(bugprone-easily-swappable-parameters) - builtin function
{
    // todo
    return NULL;
};

// we must be mindful of what's high and low bites on a given arch
static void splitSizet(size_t value, uint32_t* low_out, uint32_t* high_out)    //NOLINT(bugprone-easily-swappable-parameters)
{
    const int byte = 8;
    const int u32_size = sizeof(uint32_t)*byte;
    const unsigned int u32_max = 0xFFFFFFFF;
    *low_out  = (uint32_t)(value & u32_max);
    *high_out = (uint32_t)((value >> u32_size) & u32_max);
}

static size_t combineInts(uint32_t low, uint32_t high) {
    const int byte = 8;
    const int u32_size = sizeof(uint32_t) * byte;
    return ((size_t) high << u32_size) | low;
}


class FileHandle {
    // required pre-conditions for this handle's implementation to be sound
    static_assert(sizeof(FILE*) == sizeof(size_t));
    static_assert(alignof(FILE*) == alignof(size_t));
    static_assert(sizeof(int) == sizeof(uint32_t));

    private:
        uint32_t _fd;
        uint32_t _flags;
    
    public:
        explicit FileHandle(FILE* file_ptr) {
            // required unsafe type conversion. Assertions are made in this class to limit issues
            size_t file_handle = reinterpret_cast<size_t> (file_ptr);   // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
            
            uint32_t fd = -1;
            uint32_t flags = 0;
            splitSizet(file_handle, &fd, &flags);

            _fd = fd;
            _flags = flags;

        };

        explicit FileHandle() : _fd(-1), _flags(0) {};

        FILE* intoPtr() {
            size_t combined = combineInts(_fd, _flags);

            // required unsafe type conversion. Assertions are made in this class to limit issues
            FILE* value = reinterpret_cast<FILE*> (combined);   // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

            return value;
        }

        int id() {
            return (int) _fd;
        }
};
