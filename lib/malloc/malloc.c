#define LACKS_UNISTD_H 1
#define LACKS_FCNTL_H 1
#define LACKS_SYS_PARAM_H 1
#define LACKS_SYS_MMAN_H 1
#define LACKS_STRINGS_H 1
#define LACKS_STRING_H 1
#define LACKS_SYS_TYPES_H 1
#define LACKS_ERRNO_H 1
#define LACKS_STDLIB_H 1
#define LACKS_SCHED_H 1
#define LACKS_TIME_H 1

#define USE_LOCKS 0
#define NO_MALLOC_STATS 1
#define HAVE_MMAP 0
#define malloc_getpagesize 65536
#define USAGE_ERROR_ACTION(m,p)
#define MALLOC_FAILURE_ACTION
#define ABORT
#define ENOMEM 12
#define EINVAL 22
#define MORECORE_CONTIGUOUS 1
#define MORECORE_CANNOT_TRIM 1
#define MORECORE sbrk
#define DLMALLOC_EXPORT

#define EXPORT __attribute__((visibility("default")))

#ifdef WASM64
#define _Addr long long
#else
#define _Addr int
#endif

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned _Addr size_t;
typedef unsigned _Addr uintptr_t;
typedef _Addr ptrdiff_t;

#undef _Addr

static inline void *sbrk(ptrdiff_t increment) {
  int pages = increment >> 16;
  return (void *)__builtin_wasm_grow_memory(pages > 1 ? pages : 1);
}

EXPORT void *memcpy(void *restrict dest, const void *restrict src, size_t n);
EXPORT void *memset(void *dest, int c, size_t n);
EXPORT void *malloc(size_t);
EXPORT void free(void *);

#include "memcpy.c"
#include "memset.c"
#include "dlmalloc.c"