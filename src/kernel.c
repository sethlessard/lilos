#include "kernel.h"
#include "driver/keyboard/keyboard.h"
#include "driver/screen/screen.h"
#include "idt/idt.h"
#include "stdlib/kprint.h"

void kernelMain(void)
{
	// initialize the IDT
	Idt_init();

	// initialize the drivers
	Keyboard_init();

	// clear the screen
	Screen_clear();

	const char *str = "my first kernel with keyboard support";
	kprint(str);
	kprint_newLine();
	kprint_newLine();

	while (1)
		;
}
