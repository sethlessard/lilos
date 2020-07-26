#include <idt.h>
#include <kernel.h>

#include <driver/keyboard.h>

#include <klibc/kstdint.h>
#include <klibc/kstring.h>

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e

extern void ASM_keyboardHandler(void);
extern void outb(unsigned short port, unsigned char data);
extern void IDT_flush(uint32_t idtPtr);

// isr handlers
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

void _addIdtEntry(uint8_t num, uint32_t base, uint16_t se1, uint8_t flags);

typedef struct idt_entry
{
	uint16_t baseLow;
	uint16_t selector;
	uint8_t always0;
	uint8_t flags;
	uint16_t baseHigh;
}__attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
}__attribute((packed)) idt_ptr_t;

idt_entry_t idt[IDT_SIZE];
idt_ptr_t idtPtr;

/**
 * Initialize the idt.
 */
void IDT_init(void)
{
	idtPtr.limit = sizeof(idt_entry_t) * 256 - 1;
	idtPtr.base = (uint32_t)&idt;

	kmemset(&idt, 0, sizeof(idt_entry_t) * 256);

	// populate the built-in isr entries
	_addIdtEntry(0, (uint32_t)isr0, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(1, (uint32_t)isr1, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(2, (uint32_t)isr2, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(3, (uint32_t)isr3, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(4, (uint32_t)isr4, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(5, (uint32_t)isr5, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(6, (uint32_t)isr6, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(7, (uint32_t)isr7, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(8, (uint32_t)isr8, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(9, (uint32_t)isr9, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(10, (uint32_t)isr10, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(11, (uint32_t)isr11, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(12, (uint32_t)isr12, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(13, (uint32_t)isr13, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(14, (uint32_t)isr14, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(15, (uint32_t)isr15, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(16, (uint32_t)isr16, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(17, (uint32_t)isr17, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(18, (uint32_t)isr18, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(19, (uint32_t)isr19, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(20, (uint32_t)isr20, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(21, (uint32_t)isr21, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(22, (uint32_t)isr22, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(23, (uint32_t)isr23, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(24, (uint32_t)isr24, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(25, (uint32_t)isr25, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(26, (uint32_t)isr26, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(27, (uint32_t)isr27, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(28, (uint32_t)isr28, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(29, (uint32_t)isr29, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(30, (uint32_t)isr30, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	_addIdtEntry(31, (uint32_t)isr31, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);

	// populate the keyboard IdtEntry
	uint32_t keyboardAddress = (uint32_t)ASM_keyboardHandler;
	_addIdtEntry(0x21, (uint32_t)keyboardAddress, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);

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

	IDT_flush((uint32_t)&idtPtr);
}

/**
 * Add an IDT entry.
 * @param num the interrupt number.
 * @param base the address to the ISR handler.
 * @param selector kernel segment selector
 * @param flags the flags.
 */ 
void _addIdtEntry(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
	idt[num].baseLow = base & 0xFFFF;
	idt[num].baseHigh = (base & 0xFFFF0000) >> 16;

	idt[num].selector = selector;
	idt[num].always0 = 0;

	/*
		Uncomment the or below when user mode is active.
		It sets the interrupt gate's privilege level to 3 (user mode). 0 is kernel mode.
	*/
	idt[num].flags = flags; /* | 0x60 */
}
