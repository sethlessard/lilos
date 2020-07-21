; adapted from: https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel
bits 32
section .text
        ; multiboot spec
        align 4
        dd 0x1BADB002            ; magic
        dd 0x00                  ; flags
        dd - (0x1BADB002 + 0x00) ; checksum. magic + flags + checksum should be zero

global start

extern kernelMain

start:
    cli                          ; block interrupts
    mov esp, stack               ; set stack pointer
    push eax                     ; push the magic number to the stack to be read by kernelMain
    push ebx                     ; push the address of the grub multiboot object to the stack to be read by kernelMain
    call kernelMain
    hlt                          ; halt the CPU

section .bss
resb 8192                        ; 8KB for stack
stack:
