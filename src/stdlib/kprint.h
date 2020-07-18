#ifndef kprint_h
#define kprint_h

#include "../driver/screen/screen.h"

/**
 * Print a string.
 * @param str the string.
 */ 
void kprint(const char *str);

/**
 * Print a newline.
 */ 
void kprint_newLine(void);

/**
 * Print a character
 * @param c the character.
 */ 
void kprint_putc(char c);

#endif
