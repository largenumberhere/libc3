
#define BACKUP_ALLOC 0

#if BACKUP_ALLOC == 1
  #include "libc3MallocBackup.cpp"
#endif

#if BACKUP_ALLOC == 0
  #include "libc3MallocBucket.cpp"
#endif


