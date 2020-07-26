#include <klibc/kstdio.h>

#include <driver/screen.h>

#include <klibc/klimits.h>
#include <klibc/kstdbool.h>
#include <klibc/kstdarg.h>
#include <klibc/kstddef.h>

/**
 * Place a formatted string in a buffer.
 * @param buf the buffer to place the formatted string.
 * @param format the format string
 * @param ... the variable args
 * @returns the number of bytes written.
 */ 
int ksprintf(char* buf, const char* restrict format, ...) {
	va_list parameters;
	
	va_start(parameters, format);
	unsigned int written = kvsprintf(buf, format, parameters);
	va_end(parameters);

	return written;
}
