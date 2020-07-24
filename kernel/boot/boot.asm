; adapted from: https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel
bits 32
section .text
        ; multiboot spec
        align 4
        dd 0x1BADB002            ; magic
        dd 0x00                  ; flags
        dd - (0x1BADB002 + 0x00) ; checksum. magic + flags + checksum should be zero

global start

extern kernel_init
extern kernel_main

start:
    cli                          ; block interrupts
    mov esp, stack               ; set stack pointer
    push eax                     ; push the magic number to the stack to be read by kernel_init
    push ebx                     ; push the address of the grub multiboot object to the stack to be read by kernel_init
    call kernel_init             ; call kernel_init
    call kernel_main             ; call kernel_main
    hlt                          ; halt the CPU

section .bss
resb 8192                        ; 8KB for stack
stack:
