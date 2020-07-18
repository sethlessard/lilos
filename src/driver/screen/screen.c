#include "screen.h"

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_PER_CHAR 2
#define SCREEN_SIZE BYTES_PER_CHAR * COLUMNS_IN_LINE * LINES

extern void read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
void enableCursor(void);
void disableCursor(void);

unsigned int cursorLocation = 0;
char* videoMemory = (char*)0xb8000;

/**
 * Clear the screen.
 */
void Screen_clear(void) {
    unsigned int i = 0;
    while (i < SCREEN_SIZE) {
        videoMemory[i++] = ' ';
        videoMemory[i++] = 0x07;
    }
}

/**
 * Initialize the screen.
 */ 
void Screen_init(void) {

}


/**
 * Jump to the next line.
 */ 
void Screen_newLine(void) {
    unsigned int lineSize = BYTES_PER_CHAR * COLUMNS_IN_LINE;
    cursorLocation = cursorLocation + (lineSize - cursorLocation % (lineSize));
}

/**
 * Put a character at the current video pointer location.
 */ 
void Screen_putChar(const char c) {
    videoMemory[cursorLocation++] = c;
    videoMemory[cursorLocation++] = 0x07;
}

/**
 * Reset the cursor to the top left of the screen.
 */ 
void Screen_resetCursor(void) {
    cursorLocation = 0;
}
