#ifndef _KERNEL_KSTRING_H
#define _KERNEL_KSTRING_H 1

#include <klibc/kstddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int kmemcmp(const void *, const void *, size_t);

    /**
 * Copy a chunk of memory from one location to another.
 * @param dstptr the destination pointer.
 * @param srcptr the source pointer.
 * @param size the size in bytes of the chunk of memory.
 * @returns the destination pointer.
 */
    void *kmemcpy(void *__restrict dstptr, const void *__restrict srcptr, size_t size);

    void *kmemmove(void *, const void *, size_t);
    void *kmemset(void *, int, size_t);
    size_t kstrlen(const char *);

#ifdef __cplusplus
}
#endif

#endif
