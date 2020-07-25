#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

// TODO: define stdout file pointer

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
 * Put a character at the current video pointer location with a given background and foreground color.
 * @param c the character.
 * @param backgroundCode the background color code.
 * @param foregroundCode the foregroundColor code.
 * @returns -1 if EOF (c == \0)
 */ 
int Terminal_putcc(const char c, const char backgroundCode, const char foregroundCode);

/**
 * Put a string to the terminal.
 * @param str the string.
 */ 
void Terminal_putstr(const char* str);

/**
 * Put a string to the current video pointer location with a given foreground color and background color.
 * @param str the string.
 * @param backgroundCode the background color code.
 * @param foregroundCode the foreground color code.
 */ 
void Terminal_putstrc(const char* str, const char backgroundCode, const char foregroundCode);

/**
 * Reset the cursor to the top left of the screen.
 */
void Terminal_resetCursor(void);

#endif