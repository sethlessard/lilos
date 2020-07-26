#include <isr.h>

#include <driver/serial.h>

#include <klibc/kstdio.h>

void _handleUnimplementedISR(registers_t registers);

/**
 * Common Interrupt Service Request handler.
 * @param registers the registers.
 */
void isr_handler(registers_t registers)
{
    switch (registers.intNo)
    {
    case 0:
        // divide by 0 error
        Serial_write(SERIAL_COM1, "Interrupt: Divide by zero!");
        break;
    case 1:
        // debug code
        Serial_write(SERIAL_COM1, "Interrupt: Debug Code");
        break;
    case 2:
        // non-maskable input.
        Serial_write(SERIAL_COM1, "Interrupt: Non-maskable input");
        break;
    case 3:
        // breakpoint
        Serial_write(SERIAL_COM1, "Interrupt: Breakpoint");
        break;
    case 13:
        // general protection fault (privilege checks)
        Serial_write(SERIAL_COM1, "Interrupt: General Protection Fault");
        break;
    case 14:
        // page fault
        Serial_write(SERIAL_COM1, "Interrupt: Page Fault");
        break;
    case 0x21:
        // keyboard
        Serial_write(SERIAL_COM1, "Interrupt: Keypress");
        break;
    default:
        // TODO: print this message to serial instead
        _handleUnimplementedISR(registers);
        break;
    }
}

/**
 * Handle an unimplemented ISR.
 */
void _handleUnimplementedISR(registers_t registers)
{
    char buf[40];
    ksprintf(buf, "Unimplemented ISR: %d\n", registers.intNo);
    Serial_write(SERIAL_COM1, buf);
}
