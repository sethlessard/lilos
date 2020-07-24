#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

// TODO: setup file pointers for COM1-4

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
char Serial_read(unsigned short port);

/**
 * Write a value to a serial port.
 * @param port the serial port.
 * @param c the 
 */ 
char Serial_write(unsigned short port, const char c);

#endif
