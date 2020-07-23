#include <klibc/kstdio.h>

#include <driver/screen.h>

/**
 * Put a character to stdout.
 * @param c the character to put.
 * @returns EOF if the character was the null character (nothing was put), or 1.
 */ 
int kputc(const char c) {
    return Screen_putc(c);
}
