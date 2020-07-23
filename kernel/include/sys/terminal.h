#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

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
 * @param format the format string
 * @param ... the variable args
 * @returns the number of bytes written.
 */ 
int Terminal_printf(const char* restrict format, ...);

/**
 * Put a character at the current video pointer location.
 * @param c the character to print.
 * @returns -1 if EOF (c == \0). 
 */
int Terminal_putc(const char c);

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