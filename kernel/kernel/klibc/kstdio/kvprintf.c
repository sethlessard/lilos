#include <klibc/kstdio.h>

#include <driver/screen.h>

#include <klibc/klimits.h>
#include <klibc/kstdarg.h>
#include <klibc/kstdbool.h>
#include <klibc/kstddef.h>
#include <klibc/kstdlib.h>
#include <klibc/kstring.h>

static bool print(const char *data, size_t length)
{
	const unsigned char *bytes = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++)
		if (kputc(bytes[i]) == EOF)
			return false;
	return true;
}

/**
 * Print a formatted string.
 * @param format the format string
 * @param ... the variable args
 * @returns the number of bytes written.
 */ 
int kvprintf(const char* restrict format, va_list args) {
	va_list va;
	va_copy(va, args);

	int written = 0;
	while (*format != '\0')
	{
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%')
		{
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char *format_begun_at = format++;

		if (*format == 'c')
		{
			format++;
			char c = (char)va_arg(va, int /* char promotes to int */);
			if (!maxrem)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		}
		else if (*format == 's')
		{
			format++;
			const char *str = va_arg(va, const char *);
			size_t len = kstrlen(str);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		}
		else if (*format == 'd')
		{
			format++;
			int i = va_arg(va, int);
			char buf[16];
			char *formatted = kitoa(i, buf, 10);
			size_t len = kstrlen(formatted);
			if (!print(formatted, len))
				return -1;
			written += len;
		}
		else if (*format == 'x')
		{
			format++;
			int i = va_arg(va, int);
			char buf[16];
			char *formatted = kitoa(i, buf, 16);
			size_t len = kstrlen(formatted);
			if (!print(formatted, len))
				return -1;
			written += len;
		}
		else
		{
			format = format_begun_at;
			size_t len = kstrlen(format);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}
	va_end(va);

	return written;
}
