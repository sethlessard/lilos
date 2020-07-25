#include <driver/serial.h>

// external functions
extern char inb(unsigned short port);
extern void outb(unsigned short port, unsigned char data);

// declarations
void _initPort(short port);
int _isTransmitEmpty(short port);
int _serialReceived(short port);

/**
 * Initialize serial.
 */ 
void Serial_init(void) {
    // initialize COM1
    _initPort(SERIAL_COM1);
}

/**
 * Read a serial port.
 * @returns the value.
 */ 
char Serial_read(unsigned short port) {
    while (_serialReceived(port) == 0);
    return inb(port);
}

/**
 * Write a value to a serial port.
 * @param port the serial port.
 * @param c the value to write.
 */ 
void Serial_write(unsigned short port, const char c) {
   while (_isTransmitEmpty(port) == 0);
   outb(port, c);
}

/**
 * Initialize a serial port.
 */ 
void _initPort(short port) {
   outb(port + 1, 0x00);    // Disable all interrupts
   outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(port + 1, 0x00);    //                  (hi byte)
   outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

/**
 * Check to see if we can transmit.
 * @returns 0 if no, 0x20 if we can.
 */ 
int _isTransmitEmpty(short port) {
   return inb(port + 5) & 0x20;
}

/**
 * Check to see if a port has received a value.
 * @returns 0 if false, 1 if true.
 */
int _serialReceived(short port) {
   return inb(port + 5) & 1;
}
