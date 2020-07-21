#include <idt.h>
#include <kernel.h>
#include <keyboard.h>

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e

extern void ASM_keyboardHandler(void);
extern void outb(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idtPtr);

struct IdtEntry
{
	unsigned short int offsetLowerBits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char typeAttr;
	unsigned short int offsetHigherBits;
};

struct IdtEntry idt[IDT_SIZE];

/**
 * Initialize the idt.
 */
void Idt_init(void)
{
	unsigned long keyboardAddress;
	unsigned long idtAddress;
	unsigned long idtPtr[2];

	// populate the keyboard IdtEntry
	keyboardAddress = (unsigned long)ASM_keyboardHandler;
	idt[0x21].offsetLowerBits = keyboardAddress & 0xffff;
	idt[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	idt[0x21].zero = 0;
	idt[0x21].typeAttr = INTERRUPT_GATE;
	idt[0x21].offsetHigherBits = (keyboardAddress & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	outb(0x21, 0x20);
	outb(0xA1, 0x28);

	/* ICW3 - setup cascading */
	outb(0x21, 0x00);
	outb(0xA1, 0x00);

	/* ICW4 - environment info */
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	/* Initialization finished */

	/* mask interrupts */
	outb(0x21, 0xff);
	outb(0xA1, 0xff);

	/* fill the IDT descriptor */
	idtAddress = (unsigned long)idt;
	idtPtr[0] = (sizeof(struct IdtEntry) * IDT_SIZE) + ((idtAddress & 0xffff) << 16);
	idtPtr[1] = idtAddress >> 16;

	load_idt(idtPtr);
}
