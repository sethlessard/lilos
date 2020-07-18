#ifndef screen_h
#define screen_h

/**
 * Clear the screen.
 */
void Screen_clear(void);

/**
 * Initialize the screen.
 */
void Screen_init(void);

/**
 * Jump to the next line.
 */
void Screen_newLine(void);

/**
 * Put a character at the current video pointer location.
 */
void Screen_putChar(const char c);

/**
 * Reset the cursor to the top left of the screen.
 */
void Screen_resetCursor(void);

#endif
