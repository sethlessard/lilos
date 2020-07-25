#include <driver/screen.h>

#include <klibc/kstddef.h>

unsigned int getCursorCharLocation(unsigned int x, unsigned int y);
unsigned int getCursorColorLocation(unsigned int x, unsigned int y);

unsigned int cursorX = 0;
unsigned int cursorY = 0;
unsigned int cursorLocation = 0;
char *videoMemory = (char *)0xb8000;

/**
 * Get the cursor's character memory location for a given point.
 * @param x the x value.
 * @param y the y value.
 * @returns the cursor's character memory location.
 */ 
unsigned int getCursorCharLocation(unsigned int x, unsigned int y) {
    // TODO: implement
    return 1;
}

/**
 * Get the cursor's color code memory location for a given point.
 * @param x the x value.
 * @param y the y value.
 * @returns the cursor's color code memory location.
 */ 
unsigned int getCursorColorLocation(unsigned int x, unsigned int y) {
    return 1;
}

/**
 * Clear the screen.
 */
void Screen_clear(void)
{
    Screen_fill(COLOR_BLACK, COLOR_WHITE);
}

/**
 * Fill the background with a given color.
 * @param backgroundCode the color code to use for the background.
 * @param foregroundCode the color code to use for the foreground.
 */
void Screen_fill(const char backgroundCode, const char foregroundCode)
{
    const char colorCode = (backgroundCode << 4) + foregroundCode;
    unsigned int i = 0;
    while (i < SCREEN_SIZE)
    {
        videoMemory[i++] = ' ';
        videoMemory[i++] = colorCode;
    }
}

/**
 * Get the cursor's x location.
 * @returns the x location.
 */
unsigned int Screen_getCursorX()
{
    return cursorX;
}

/**
 * Get the cursor's y location.
 * @returns the y location.
 */
unsigned int Screen_getCursorY()
{
    return cursorY;
}

/**
 * Put a character on the screen at the current location of the cursor.
 * @param c the character.
 * @returns EOF if the character passed was the null character, or 1 if successful.
 */
int Screen_putc(const char c)
{
    return Screen_putcc(c, COLOR_BLACK, COLOR_LIGHT_GRAY);
}

/**
 * Put a character on the screen at the current location of the cursor.
 * @param c the character.
 * @param backgroundCode the background color code to use.
 * @param foregroundCode the foreground color code to use.
 * @returns EOF if the character passed was the null character, or 1 if successful.
 */
int Screen_putcc(const char c, const char backgroundCode, const char foregroundCode)
{
    const char colorCode = (backgroundCode << 4) + foregroundCode;
    switch (c)
    {
    // backspace
    case '\b':
        videoMemory[--cursorLocation] = 0x07;
        videoMemory[--cursorLocation] = ' ';
        // if we've backspaced all the way to the left, decrement cursorY
        if ((--cursorX % (COLUMNS_IN_LINE - 1)) == 0)
        {
            --cursorY;
        }
        return 1;
    // newline
    case '\n':
        cursorX = 0;
        ++cursorY;
        cursorLocation = cursorLocation + (LINE_SIZE - cursorLocation % (LINE_SIZE));
        return 1;
    case 0:
        return EOF;
    default:
        // print the character
        videoMemory[cursorLocation++] = c;
        videoMemory[cursorLocation++] = colorCode;
        ++cursorX;
    }
    return 1;
}

/**
 * Set the cursor's location.
 * Set x or y to -1 use the current x or y value of the cursor.
 * @param x the x location.
 * @param y the y location.
 * @returns -1 if there was an error, or 1.
 */
int Screen_setCursorLocation(int x, int y)
{
    // TODO: validate x, y
    cursorX = x;
    cursorY = y;
    // TODO: update hardware cursor
    return 1;
}
