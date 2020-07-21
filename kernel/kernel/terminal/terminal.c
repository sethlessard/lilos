#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <kstring.h>
#include <sys/terminal.h>

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_PER_CHAR 2
#define SCREEN_SIZE BYTES_PER_CHAR *COLUMNS_IN_LINE *LINES
#define LINE_SIZE BYTES_PER_CHAR * COLUMNS_IN_LINE

#define BAM "lilos > "
#define BAM_LENGTH kstrlen(BAM)

void _writeBam(void);

unsigned int cursorLocation = 0;
char *videoMemory = (char *)0xb8000;

/**
 * Clear the screen.
 */
void Terminal_clear(void)
{
    unsigned int i = 0;
    while (i < SCREEN_SIZE)
    {
        videoMemory[i++] = ' ';
        videoMemory[i++] = 0x07;
    }
}

/**
 * Initialize the screen.
 */
void Terminal_init(void)
{
	_writeBam();
}

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (Terminal_putChar(bytes[i]) == EOF)
			return false;
	return true;
}

int Terminal_printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = kstrlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd') {
			format++;
			int i = va_arg(parameters, int);
			char buf[16];
			char* formatted = itoa(i, buf, 10);
			size_t len = kstrlen(formatted);
			if (!print(formatted, len))
				return -1;
			written += len;
		} else {
			format = format_begun_at;
			size_t len = kstrlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}

/**
 * Put a character at the current video pointer location.
 */
int Terminal_putChar(const char c)
{
	switch (c) {
		// backspace
		case '\b':
			if (cursorLocation > 0) {
				videoMemory[--cursorLocation] = 0x07;
				videoMemory[--cursorLocation] = ' ';
			}
			break;
		// newline
		case '\n':
			cursorLocation = cursorLocation + (LINE_SIZE - cursorLocation % (LINE_SIZE));
			return 1;
		case 0:
			return EOF;
		default:
			// print the character
			videoMemory[cursorLocation++] = c;
    		videoMemory[cursorLocation++] = 0x07;
	}
	return 1;
}

/**
 * Put a string to the terminal.
 * @param str the string.
 */ 
void Terminal_putStr(const char* str) {
    Terminal_printf("%s\n", str);
}

/**
 * Reset the cursor to the top left of the screen.
 */
void Terminal_resetCursor(void)
{
    cursorLocation = 0;
}

void _writeBam(void) {
	Terminal_printf(BAM);
}
