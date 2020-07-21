
global load_idt

; load the IDT from C kernel.
load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti                          ; turn on interrupts
    ret
