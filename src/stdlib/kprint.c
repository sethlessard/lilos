#include "kprint.h"

/**
 * Print a string.
 * @param str the string.
 */
void kprint(const char *str)
{
    unsigned int i = 0;
    while (str[i])
    {
        kprint_putc(str[i++]);
    }
}

/**
 * Print a newline.
 */
void kprint_newLine(void)
{
    Screen_newLine();
}

/**
 * Print a character
 * @param c the character.
 */
void kprint_putc(char c)
{
    if (c == '\n')
    {
        kprint_newLine();
        return;
    }
    Screen_putChar(c);
}
