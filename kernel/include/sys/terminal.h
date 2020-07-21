#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <stddef.h>

#define EOF -1

/**
 * Clear the screen.
 */
void Terminal_clear(void);

/**
 * Initialize the screen.
 */
void Terminal_init(void);

/**
 * Print a formatted string.
 */ 
int Terminal_printf(const char* restrict format, ...);

/**
 * Put a character at the current video pointer location.
 * @param c the character to print.
 * @returns -1 if EOF (c == \0). 
 */
int Terminal_putChar(const char c);

/**
 * Put a string to the terminal.
 * @param str the string.
 */ 
void Terminal_putStr(const char* str);

/**
 * Reset the cursor to the top left of the screen.
 */
void Terminal_resetCursor(void);

#endif