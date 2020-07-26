#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

// TODO: setup file pointers for COM1-4
#include <klibc/kstddef.h>
#include <klibc/kstdint.h>

#define SERIAL_COM1 0x3F8
#define SERIAL_COM2 0x2F8
#define SERIAL_COM3 0x3E8
#define SERIAL_COM4 0x2EB

/**
 * Initialize serial.
 */
void Serial_init(void);

/**
 * Read a serial port.
 * @returns the value.
 */
char Serial_readb(unsigned short port);

/**
 * Write a string to a serial port.
 * @param port the serial port.
 * @param str the string or data.
 * @returns the number of bytes written.
 */
size_t Serial_write(uint16_t port, const char *str);

/**
 * Write a value to a serial port.
 * @param port the serial port.
 * @param c the the character to write.
 * @returns EOF if failed, 1 if written.
 */
uint32_t Serial_writeb(uint16_t port, const char c);

#endif
