#include <klibc/kstdio.h>

#include <driver/screen.h>

#include <klibc/klimits.h>
#include <klibc/kstdarg.h>
#include <klibc/kstdbool.h>
#include <klibc/kstddef.h>
#include <klibc/kstdlib.h>
#include <klibc/kstring.h>

/**
 * Print a formatted string to a buffer.
 * @param buf the buffer.
 * @param format the format string
 * @param ... the variable args
 * @returns the number of bytes written.
 */ 
int kvsprintf(char* buf, const char* restrict format, va_list args) {
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
            kmemcpy(buf + written, format, amount);
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
            kmemcpy(buf + written, &c, sizeof(c));
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
            kmemcpy(buf + written, str, len);
			written += len;
		}
		else if (*format == 'd')
		{
			format++;
			int i = va_arg(va, int);
			char intBuf[16];
			kitoa(i, intBuf, 10);
			size_t len = kstrlen(intBuf);
            kmemcpy(buf + written, intBuf, len);
			written += len;
		}
		else if (*format == 'x')
		{
			format++;
			int i = va_arg(va, int);
			char intBuf[16];
			kitoa(i, intBuf, 16);
			size_t len = kstrlen(intBuf);
			kmemcpy(buf + written, "0x", 2);
            kmemcpy(buf + written + 2, intBuf, len);
			written += 2 + len;
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
            kmemcpy(buf + written, format, len);
			written += len;
			format += len;
		}
	}
	va_end(va);

	return written;
}
