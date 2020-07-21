
global inb
global outb

; read a byte from a port.
inb:
    mov edx, [esp + 4]          ; read port (unsigned short)
    in al, dx
    ret

; write a byte of data to a port.
outb:
    mov edx, [esp + 4]          ; read port (unsigned short)
    mov al, [esp + 4 + 4]       ; read data (unsigned char)
    out dx, al
    ret
