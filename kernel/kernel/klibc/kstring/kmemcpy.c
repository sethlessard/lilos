#include <klibc/kstring.h>

/**
 * Copy a chunk of memory from one location to another.
 * @param dstptr the destination pointer.
 * @param srcptr the source pointer.
 * @param size the size in bytes of the chunk of memory.
 * @returns the destination pointer.
 */ 
void* kmemcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}
