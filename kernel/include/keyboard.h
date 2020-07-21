#ifndef _KERNEL_DRIVER_KEYBOARD_H
#define _KERNEL_DRIVER_KEYBOARD_H

/**
 * Handle a keypress.
 */
void Keyboard_handleKeypress(void);

/**
 * Initialize the keyboard.
 */
void Keyboard_init(void);

#endif