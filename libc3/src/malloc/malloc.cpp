
#define BACKUP_ALLOC 1

#if BACKUP_ALLOC == 1
  #include "mallocBackup.cpp"
#endif

#if BACKUP_ALLOC == 0
  #include "mallocBucket.cpp"
#endif


