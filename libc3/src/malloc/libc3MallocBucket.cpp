#include "../../include/libc3Debug.hpp"
#include "../../include/libc3Ints.hpp"
#include "../../include/libc3Mangled.hpp"

/*
    These buckets are intended to approximately model the data cache sizes of
   some contemporary CPUS of 2025. Namely, the Ryzen 5 2600, Ryzen AMD Ryzen™ 9
   9950X, and Intel i9-13900k.

    Each bucket (except KERNELALLOC) has capacity for 16 items of exactly 1/16th
   of the max size. KERNELALLOC is not really a bucket, it just denotes a raw
   allocation of the size requested (rounded up to the nearest page). Only
   KERNELALLOC items will contain size_t length, and size_t capacity as the
   first 128 BITS (16 byes) of the allocation. UNINITALIZED referss to a bucket
   that has not been allocated

*/
enum BUCKET_KIND : uint8_t {
  BUCKET_UNINITALIZED,
  BUCKET_4K,
  BUCKET_16K,
  BUCKET_64K,
  BUCKET_1M,
  BUCKET_2M,
  BUCKET_16M,
  BUCKET_64M,
  BUCKET_KERNELALLOC
};

enum BYTESIZES : size_t {
  KILOBYTE = 1024,
  MEGABYTE = (size_t)(1024 * 1024),
};

class Bucket {
private:
  Libc3RawArray<char> _allocatedBuffer = {};
  BUCKET_KIND _bucketKind = {};

public:
  Bucket() {}

  size_t getBucketCapacity() {
    size_t i = 0;
    switch (_bucketKind) {
    case BUCKET_UNINITALIZED:
      i = 0;
      break;
    case BUCKET_4K:
      i = 4 * KILOBYTE;
      break;
    case BUCKET_16K:
      i = 16 * KILOBYTE;
      break;
    case BUCKET_64K:
      i = 64 * KILOBYTE;
      break;
    case BUCKET_1M:
      i = MEGABYTE;
      break;
    case BUCKET_2M:
      i = 2 * MEGABYTE;
      break;
    case BUCKET_16M:
      i = 16 * MEGABYTE;
      break;
    case BUCKET_64M:
      i = 64 * MEGABYTE;
      break;
    case BUCKET_KERNELALLOC:
      TODO();

      break;
    default:
      UNREACHABLE();
    }

    return i;
  }

  bool isInitalized() {
    if (_bucketKind == BUCKET_UNINITALIZED) {
      return false;
    }

    return true;
  }

  void initBucketKernel(size_t min_bytes) { TODO(); }

  void initStandardBucket(BUCKET_KIND kind) {
    if (kind == BUCKET_UNINITALIZED || kind == BUCKET_KERNELALLOC) {
      PANIC();
    }

    TODO();
    TODO("mrrr")
  }

  bool freeItem(void *ptr) {
    TODO();
    return false;
  }
};

// template class Libc3Array<Bucket*>;

template class Libc3Array<Bucket *>;

enum { MAX_BUCKETS = (100) };

static Bucket arr[MAX_BUCKETS];
static Libc3Array<Bucket> buckets = Libc3Array<Bucket>();
static bool first_run = true;

extern "C" void *libc3Malloc(size_t size) {
  if (first_run) {
    first_run = false;
    libc3Memset(arr, 0, sizeof(Bucket) * MAX_BUCKETS);
    buckets = Libc3Array<Bucket>((Bucket *)arr, MAX_BUCKETS);
  }

  for (int i = 0; i < MAX_BUCKETS; i++) {
    Bucket b = buckets.get(i);
    bool init = b.isInitalized();

    if (init) {
      libc3WriteStdout("Instantiated\n");
    }
  }

  return NULL;
}
extern "C" void libc3Free(void *ptr) { return; }
