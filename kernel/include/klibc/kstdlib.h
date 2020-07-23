#ifndef _KERNEL_STDLIB_H
#define _KERNEL_STDLIB_H

/**
 * Converts an integer value into a null-terminated string using the specified
 * base and stores the result in the str array.
 * @param value the value to convert.
 * @param str the character buffer to store the null-terminated string.
 * @param base the base of the integer, between 2 and 36.
 */
char* kitoa(int value, char *str, int base);

#endif
