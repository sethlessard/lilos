
global IDT_flush

; load the IDT from C kernel.
IDT_flush:
    mov edx, [esp + 4]
    lidt [edx]
    sti                          ; turn on interrupts
    ret
