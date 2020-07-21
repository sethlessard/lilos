#include <stdio.h>

#if defined(__is_libk)
#include <kernel/terminal.h>
#include <screen.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
	Terminal_putChar((char)ic);
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}
