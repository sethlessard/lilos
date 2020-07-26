global GDT_flush

GDT_flush:
    mov eax, [esp + 4]              ; move gdt_pointer pointer into eax
    lgdt [eax]                      ; load the gdt

    mov ax, 0x10                    ; 0x10 is the offset to the data segment in the gdt.
    mov ds, ax                      ; load the data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush                 ; 0x08 is the offset to the kernel code segment

.flush:
    ret

