#ifndef _KERNEL_ISR_H
#define _KERNEL_ISR_H

#include <klibc/kstdint.h>

typedef struct registers
{
    uint32_t ds;                                     // data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // registers pushed by pusha
    uint32_t intNo, errCode;                         // interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss;           // pushed by the processor automatically
} registers_t;

/**
 * Common Interrupt Service Request handler.
 * @param registers the registers.
 */
void isr_handler(registers_t registers);

#endif