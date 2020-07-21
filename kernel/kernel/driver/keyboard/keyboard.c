#include <keyboard.h>
#include <keyboardmap.h>
#include <sys/terminal.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C

extern char inb(unsigned short port);
extern void outb(unsigned short port, unsigned char data);

/**
 * Handle a keypress.
 */
void Keyboard_handleKeypress(void)
{
    unsigned char status;
    char keycode;

    /* write EOI */
    outb(0x20, 0x20);

    status = inb(KEYBOARD_STATUS_PORT);
    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01)
    {
        keycode = inb(KEYBOARD_DATA_PORT);
        if (keycode < 0)
            return;

        if (keycode == ENTER_KEY_CODE)
        {
            // TODO: instead of printing straight to the screen, add support for
            // subscribing to keyboard events.
            Terminal_putChar('\n');
            return;
        }

        // TODO: instead of printing straight to the screen, add support for
        // subscribing to keyboard events.
        Terminal_putChar(keyboardmap[(unsigned char)keycode]);
    }
}

/**
 * Initialize the keyboard.
 */
void Keyboard_init(void)
{
    outb(0x21, 0xFD);
}
