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

	// clear the terminal
	Terminal_clear();

	const char *str = "Uh >";
	Terminal_printf(str);

	while (1);
}
