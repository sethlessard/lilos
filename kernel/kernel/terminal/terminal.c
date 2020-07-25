#include <sys/terminal.h>

#include <driver/screen.h>

#include <klibc/klimits.h>
#include <klibc/kstdbool.h>
#include <klibc/kstdarg.h>
#include <klibc/kstdio.h>
#include <klibc/kstddef.h>
#include <klibc/kstdlib.h>
#include <klibc/kstring.h>

#define BAM "lilos > "
#define BAM_LENGTH kstrlen(BAM)

void _writeBam(void);

unsigned int lineLength = 0;

/**
 * Clear the screen.
 */
void Terminal_clear(void)
{
	Screen_clear();
}

/**
 * Initialize the screen.
 */
void Terminal_init(void)
{
	lineLength = 0;
	_writeBam();
}

/**
 * Print a formatted string to the terminal.
 * @param format the format.
 * @param ... the va_args
 */ 
int Terminal_printf(const char *restrict format, ...)
{
	va_list parameters;

	va_start(parameters, format);
	int bytesWritten = kvprintf(format, parameters);
	va_end(parameters);
	
	return bytesWritten;
}

/**
 * Put a character at the current video pointer location.
 */
int Terminal_putc(const char c)
{
	return Terminal_putcc(c, COLOR_BLACK, COLOR_LIGHT_GRAY);
}

/**
 * Put a character at the current video pointer location with a given background and foreground color.
 * @param c the character.
 * @param backgroundCode the background color code.
 * @param foregroundCode the foregroundColor code.
 * @returns -1 if EOF (c == \0)
 */ 
int Terminal_putcc(const char c, const char backgroundCode, const char foregroundCode) {
	switch (c) {
		case '\b':
			if (lineLength == 0) return 1;
			--lineLength;
			break;
		case '\n':
			lineLength = 0;
			// TODO: execute line
			// TODO: print bam
			break;
	}
	Screen_updateCursorLocation();
	if (kputcc(c, backgroundCode, foregroundCode) != EOF) {
		++lineLength;
		Screen_updateCursorLocation();
		return 1;
	};
	return EOF;
}

/**
 * Put a string to the terminal.
 * @param str the string.
 */
void Terminal_putstr(const char *str)
{
	Terminal_printf("%s\n", str);
	Screen_updateCursorLocation();
}

/**
 * Put a string to the current video pointer location with a given foreground color and background color.
 * @param str the string.
 * @param backgroundCode the background color code.
 * @param foregroundCode the foreground color code.
 */ 
void Terminal_putstrc(const char* str, const char backgroundCode, const char foregroundCode) {
	unsigned int i = 0;
	char c;
	while ((c = str[i++]) != 0) {
		kputcc(c, backgroundCode, foregroundCode);
	}
	Screen_updateCursorLocation();
}

void _writeBam(void)
{	
	Terminal_putstrc(BAM, COLOR_BLACK, COLOR_GREEN);
}
