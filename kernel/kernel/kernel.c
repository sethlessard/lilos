#include <kernel.h>
#include <keyboard.h>
#include <idt.h>
#include <sys/terminal.h>

void kernelMain(void)
{
	// initialize the IDT
	Idt_init();

	// initialize the drivers
	Keyboard_init();

	// initialize the terminal
	Terminal_init();

	while (1);
}
