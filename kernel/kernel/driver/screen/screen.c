#include <driver/screen.h>

#include <klibc/kstddef.h>
#include <klibc/kstdint.h>

#define VIDEO_MEM 0xb8000

extern char inb(unsigned short port);
extern void outb(unsigned short port, unsigned char data);

void _enableCursor(uint8_t topScanLine, uint8_t bottomScanLine);
unsigned int _getCursorCharLocation(unsigned int x, unsigned int y);
unsigned int _getCursorColorLocation(unsigned int x, unsigned int y);
void _updateCursor(unsigned int x, unsigned int y);

unsigned int cursorX = 0;
unsigned int cursorY = 0;
unsigned int cursorLocation = 0;
char *videoMemory = (char *)VIDEO_MEM;

// TODO: add a generic write(char* data);

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
unsigned int Screen_getCursorX(void)
{
    return cursorX;
}

/**
 * Get the cursor's y location.
 * @returns the y location.
 */
unsigned int Screen_getCursorY(void)
{
    return cursorY;
}

/**
 * Initialize the screen.
 */
void Screen_init(void)
{
    // enable the cursor
    _enableCursor(0, 25); // osdev.org says it's usually 15

    // set cursor location (0,0)
    cursorX = 0;
    cursorY = 0;
    _updateCursor(cursorX, cursorY);
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
        // if we've backspaced all the way to the left, decrement cursorY
        if ((--cursorX % (VGA_WIDTH - 1)) == 0)
        {
            --cursorY;
            // TODO: reset cursorX to previous non-whitespace. For now, put at x = 79
            cursorX = VGA_WIDTH - 1;
            videoMemory[_getCursorCharLocation(0, cursorY + 1)] = ' ';
            videoMemory[_getCursorColorLocation(0, cursorY + 1)] = 0x07;
            return;
        }

        videoMemory[_getCursorCharLocation(cursorX, cursorY)] = ' ';
        videoMemory[_getCursorColorLocation(cursorX, cursorY)] = 0x07;
        return 1;
    // newline
    case '\n':
        cursorX = 0;
        ++cursorY;
        return 1;
    case 0:
        return EOF;
    default:
        videoMemory[_getCursorCharLocation(cursorX, cursorY)] = c;
        videoMemory[_getCursorColorLocation(cursorX, cursorY)] = colorCode;
        // print the character
        if ((++cursorX % (VGA_WIDTH)) == 0)
        {
            ++cursorY;
            cursorX = 0;
        }
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
    _updateCursor(cursorX, cursorY);
    return 1;
}

/**
 * Force the screen to update the hardware cursor location.
 */
void Screen_updateCursorLocation(void)
{
    _updateCursor(cursorX, cursorY);
}

/**
 * Enable the hardware cursor.
 * @param 
 */
void _enableCursor(uint8_t topScanLine, uint8_t bottomScanLine)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | topScanLine);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | bottomScanLine);
}

/**
 * Get the cursor's character memory location for a given point.
 * 
 * Each screen character is represented by a two byte chunk of memory:
 * 
 *      15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
 *      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 *      v   v   v   v   v   v   v   v   v   v   v   v   v   v   v   v
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      | Character Code            | BG Color Code | FG Color Code |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 
 * @param x the x value.
 * @param y the y value.
 * @returns the cursor's character memory location (bits 15-8).
 */
unsigned int _getCursorCharLocation(unsigned int x, unsigned int y)
{
    return x * 2 + (y * BYTES_PER_LINE);
}

/**
 * Get the cursor's color code memory location for a given point.
 * @param x the x value.
 * @param y the y value.
 * @returns the cursor's color code memory location (bits 7-0).
 */
unsigned int _getCursorColorLocation(unsigned int x, unsigned int y)
{
    return _getCursorCharLocation(x, y) + 1;
}

/**
 * Update the position of the hardware cursor.
 * @param x the x location.
 * @param y the y location.
 */
void _updateCursor(unsigned int x, unsigned int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
