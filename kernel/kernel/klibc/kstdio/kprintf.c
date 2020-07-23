#include <klibc/kstdio.h>

#include <driver/screen.h>

#include <klibc/klimits.h>
#include <klibc/kstdbool.h>
#include <klibc/kstdarg.h>
#include <klibc/kstddef.h>

/**
 * Print a formatted string.
 * @param format the format string
 * @param ... the variable args
 * @returns the number of bytes written.
 */ 
int kprintf(const char* restrict format, ...) {
	va_list parameters;
	
	va_start(parameters, format);
	unsigned int written = kvprintf(format, parameters);
	va_end(parameters);

	return written;
}
