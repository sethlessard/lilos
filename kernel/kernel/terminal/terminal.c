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
	if (kputc(c) != EOF) {
		++lineLength;
		return 1;
	};
	return EOF;
}

/**
 * Put a string to the terminal.
 * @param str the string.
 */
void Terminal_putStr(const char *str)
{
	Terminal_printf("%s\n", str);
}

void _writeBam(void)
{
	kprintf(BAM);
}
