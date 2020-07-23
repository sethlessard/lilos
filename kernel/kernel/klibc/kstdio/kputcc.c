#include <klibc/kstdio.h>

#include <driver/screen.h>

/**
 * Put a character to stdout with a given background and foreground color.
 * @param c the character to put.
 * @param backgroundCode the background color code.
 * @param foregroundCode the foreground color code.
 * @returns EOF if the character was the null character (nothing was put), or 1.
 */ 
int kputcc(const char c, const char backgroundCode, const char foregroundCode) {
    return Screen_putcc(c, backgroundCode, foregroundCode);
}
