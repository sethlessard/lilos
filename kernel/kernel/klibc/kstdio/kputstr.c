#include <klibc/kstdio.h>

#include <driver/screen.h>

/**
 * Put a string to stdout.
 * @param str the string to put.
 * @returns the number of bytes written.
 */ 
int kputstr(const char* str) {
    return kprintf("%s\n", str);
}
