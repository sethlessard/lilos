#ifndef _KERNEL_SCREEN_H
#define _KERNEL_SCREEN_H

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_PER_CHAR 2
#define SCREEN_SIZE BYTES_PER_CHAR * COLUMNS_IN_LINE * LINES
#define LINE_SIZE BYTES_PER_CHAR * COLUMNS_IN_LINE

#define COLOR_BLACK             0x0
#define COLOR_BLUE              0x1
#define COLOR_GREEN             0x2
#define COLOR_CYAN              0x3
#define COLOR_RED               0x4
#define COLOR_MAGENTA           0x5
#define COLOR_BROWN             0x6
#define COLOR_LIGHT_GRAY        0x7
#define COLOR_DARK_GRAY         0x8
#define COLOR_LIGHT_BLUE        0x9
#define COLOR_LIGHT_GREEN       0xA
#define COLOR_LIGHT_CYAN        0xB
#define COLOR_LIGHT_RED         0xC
#define COLOR_LIGHT_MAGENTA     0xD
#define COLOR_LIGHT_YELLOW      0xE
#define COLOR_WHITE             0xF

/**
 * Clear the screen.
 */ 
void Screen_clear(void);

/**
 * Fill the background with a given color.
 * @param backgroundCode the color code to use for the background.
 * @param foregroundCode the color code to use for the foreground.
 */ 
void Screen_fill(const char backgroundCode, const char foregroundCode);

/**
 * Get the cursor's x location.
 * @returns the x location.
 */ 
unsigned int Screen_getCursorX(void);

/**
 * Get the cursor's y location.
 * @returns the y location.
 */ 
unsigned int Screen_getCursorY(void);

/**
 * Put a character on the screen at the current location of the cursor.
 * @param c the character.
 * @returns EOF if the character passed was the null character, or 1 if successful.
 */ 
int Screen_putc(const char c);

/**
 * Put a character on the screen at the current location of the cursor.
 * @param c the character.
 * @param backgroundCode the background color code to use.
 * @param foregroundCode the foreground color code to use.
 * @returns EOF if the character passed was the null character, or 1 if successful.
 */
int Screen_putcc(const char c, const char backgroundCode, const char foregroundCode);

/**
 * Set the cursor's location.
 * Set x or y to -1 use the current x or y value of the cursor.
 * @param x the x location.
 * @param y the y location.
 * @returns -1 if there was an error, or 1.
 */ 
int Screen_setCursorLocation(int x, int y);

#endif
