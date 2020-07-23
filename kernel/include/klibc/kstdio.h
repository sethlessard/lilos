#ifndef _KERNEL_KSTDIO_H
#define _KERNEL_KSTDIO_H

#include <klibc/kstdarg.h>

/**
 * Print a formatted string.
 * @param format the format string
 * @param ... the variable args
 * @returns the number of bytes written.
 */ 
int kprintf(const char* restrict format, ...);

/**
 * Put a character to stdout.
 * @param c the character to put.
 * @returns EOF if the character was the null character (nothing was put), or 1.
 */ 
int kputc(const char c);

/**
 * Put a character to stdout with a given background and foreground color.
 * @param c the character to put.
 * @param backgroundCode the background color code.
 * @param foregroundCode the foreground color code.
 * @returns EOF if the character was the null character (nothing was put), or 1.
 */ 
int kputcc(const char c, const char backgroundCode, const char foregroundCode);

/**
 * Put a string to stdout.
 * @param str the string to put.
 * @returns the number of bytes written.
 */ 
int kputstr(const char* str);

/**
 * Print a formatted string.
 * @param format the format string
 * @param ... the variable args
 * @returns the number of bytes written.
 */ 
int kvprintf(const char* restrict format, va_list parameters);

#endif
