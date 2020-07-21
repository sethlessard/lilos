
global inb
global outb

; read a byte from a port.
inb:
    mov edx, [esp + 4]
    in al, dx
    ret

; write a byte of data to a port.
outb:
    mov edx, [esp + 4]
    mov al, [esp + 4 + 4]
    out dx, al
    ret
