
CC = gcc
VERSION = 1000
PROG = kernel-${VERSION}
KSRCS = ${wildcard kernel/kernel/driver/keyboard/*.c} \
	    ${wildcard kernel/kernel/idt/*.c} \
		${wildcard kernel/kernel/libc/stdlib/*.c} \
		${wildcard kernel/kernel/libc/string/*.c } \
		${wildcard kernel/kernel/terminal/*.c} \
	    ${wildcard kernel/kernel/*.c }
KOBJS = ${KSRCS:.c=.o}
LIBCOBJS = ${wildcard libc/stdio/*.o} \
		   ${wildcard libc/stdlib/*.o} \
		   ${wildcard libc/string/*.o}
WARN    = -W -Wall -Wstrict-prototypes -Wmissing-prototypes
CFLAGS  = -ffreestanding -O2 -DMODULE -D__KERNEL__ -nostdinc ${WARN}

all: ${PROG}

boot.o:
	nasm -f elf32 boot.asm -o boot.o
	
%.o: %.c
	gcc -m32 -Ikernel/include ${CFLAGS} -c -o $@ $^

${PROG}: boot.o ${KOBJS} ${LIBCOBJS}
	ld -m elf_i386 -T link.ld -o ${PROG} boot.o ${KOBJS} ${LIBCOBJS}

boot.iso: ${PROG}
	mkdir -p iso/boot/grub
	cp ${PROG} iso/boot
	cp grub.cfg iso/boot/grub
	grub-mkrescue -o boot.iso iso/
	
.PHONY: run
run: ${PROG}
	qemu-system-i386 -kernel ${PROG}

.PHONY: runiso
runiso: boot.iso
	qemu-system-i386 -cdrom boot.iso

.PHONY: clean
clean:
	rm -f ${KOBJS}
	rm -f *.o
	rm -f ${PROG}
