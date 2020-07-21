extern Keyboard_handleKeypress

global ASM_keyboardHandler

ASM_keyboardHandler:
    call Keyboard_handleKeypress
    iretd
