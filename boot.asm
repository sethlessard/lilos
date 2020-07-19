; adapted from: 
https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel
bits 32
section .text
        ; multiboot spec
        align 4
        dd 0x1BADB002            ; magic
        dd 0x00                  ; flags
        dd - (0x1BADB002 + 0x00) ; checksum. magic + flags + checksum should be zero

global start
global load_idt
global BOOT_keyboardHandler
global read_port
global write_port

extern kernelMain
extern Keyboard_handleKeypress

BOOT_keyboardHandler:
    call Keyboard_handleKeypress
    iretd

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti                          ; turn on interrupts
    ret

start:
    cli                          ; block interrupts
    mov esp, stack               ; set stack pointer
    call kernelMain
    hlt                          ; halt the CPU

read_port:
    mov edx, [esp + 4]
    in al, dx
    ret

write_port:
    mov edx, [esp + 4]
    mov al, [esp + 4 + 4]
    out dx, al
    ret


section .bss
resb 8192                        ; 8KB for stack
stack:
