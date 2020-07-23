#include <kernel.h>
#include <idt.h>

#include <driver/keyboard.h>

#include <sys/terminal.h>

typedef multiboot_memory_map_t mmap_entry_t;

void kernelMain(multiboot_info_t *mbd, unsigned int magic)
{
	// initialize the screen
	Terminal_clear();
	Terminal_printf("%d", 33);

	// verify the multiboot flag
	if ((mbd->flags & 1) == 0)
	{
		Terminal_printf("Error. Expecting the first bit of the multiboot flag to be set.\n");
		while (1)
			;
	}

	// TODO: outsource memory management 
	unsigned int freeMemoryBytes = 0;
	unsigned int reservedMemoryBytes = 0;
	unsigned int badBytes = 0;
	mmap_entry_t *entry = mbd->mmap_addr;
	while (entry < mbd->mmap_addr + mbd->mmap_length)
	{
		switch (entry->type)
		{
		case MULTIBOOT_MEMORY_AVAILABLE:
			freeMemoryBytes += entry->len;
			break;
		case MULTIBOOT_MEMORY_RESERVED:
			reservedMemoryBytes += entry->len;
			break;
		case MULTIBOOT_MEMORY_NVS:
			break;
		case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
			break;
		case MULTIBOOT_MEMORY_BADRAM:
			badBytes += entry->len;
			break;
		default:
			break;
		}
		// get the next entry
		entry = (mmap_entry_t *)((unsigned int)entry + entry->size + sizeof(entry->size));
	}

	// initialize the IDT
	Idt_init();

	// initialize the drivers
	Keyboard_init();

	// initialize the terminal
	Terminal_clear();
	Terminal_printf("Free bytes: %d\n", freeMemoryBytes);
	Terminal_printf("Reserved Bytes: %d\n", reservedMemoryBytes);
	Terminal_printf("Bad Bytes: %d\n", badBytes);
	Terminal_printf("\n");
	Terminal_init();
	
	while (1)
		;
}
