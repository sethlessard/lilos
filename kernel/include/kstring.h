#ifndef _KERNEL_KSTRING_H
#define _KERNEL_KSTRING_H 1

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int kmemcmp(const void*, const void*, size_t);
void* kmemcpy(void* __restrict, const void* __restrict, size_t);
void* kmemmove(void*, const void*, size_t);
void* kmemset(void*, int, size_t);
size_t kstrlen(const char*);

#ifdef __cplusplus
}
#endif

#endif
