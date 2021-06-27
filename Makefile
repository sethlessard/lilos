
CC = gcc
VERSION = 1000
PROG = kernel-${VERSION}
KASMSRCS = ${wildcard kernel/boot/gdt/*.asm} \
		   ${wildcard kernel/boot/idt/handlers/*.asm} \
	 	   ${wildcard kernel/boot/idt/*.asm} \
		   ${wildcard kernel/boot/ports/*.asm} \
		   ${wildcard kernel/boot/*.asm}
KASMOBJS = ${KASMSRCS:.asm=.o}
KSRCS = ${wildcard kernel/kernel/driver/keyboard/*.c} \
		${wildcard kernel/kernel/driver/screen/*.c} \
		${wildcard kernel/kernel/driver/serial/*.c} \
		${wildcard kernel/kernel/gdt/*.c} \
	    ${wildcard kernel/kernel/idt/*.c} \
		${wildcard kernel/kernel/klibc/kstdio/*.c} \
		${wildcard kernel/kernel/klibc/kstdlib/*.c} \
		${wildcard kernel/kernel/klibc/kstring/*.c } \
		${wildcard kernel/kernel/terminal/*.c} \
	    ${wildcard kernel/kernel/*.c }
KOBJS = ${KSRCS:.c=.o}
LIBCOBJS = ${wildcard libc/stdio/*.o} \
		   ${wildcard libc/stdlib/*.o} \
		   ${wildcard libc/string/*.o}
WARN    = -W -Wall -Wstrict-prototypes -Wmissing-prototypes
CFLAGS  = -ffreestanding -O2 -DMODULE -D__KERNEL__ -nostdinc ${WARN} -ggdb

all: ${PROG}

%.o: %.asm
	nasm -f elf32 -o $@ $^
	
%.o: %.c
	gcc -m32 -Ikernel/include ${CFLAGS} -c -o $@ $^

${PROG}: ${KASMOBJS} ${KOBJS} ${LIBCOBJS}
	ld -m elf_i386 -T link.ld -o ${PROG} ${KASMOBJS} ${KOBJS} ${LIBCOBJS}

boot.iso: ${PROG}
	mkdir -p iso/boot/grub
	cp ${PROG} iso/boot
	cp grub.cfg iso/boot/grub
	grub-mkrescue -o boot.iso iso/
	
.PHONY: run
run: ${PROG}
	qemu-system-i386 -kernel ${PROG}

.PHONY: debug
debug: ${PROG}
	qemu-system-i386 -S -s -kernel ${PROG}

.PHONY: runiso
runiso: boot.iso
	qemu-system-i386 -cdrom boot.iso

.PHONY: clean
clean:
	rm -f ${KASMOBJS} ${KOBJS}
	rm -f *.o
	rm -f ${PROG}
	rm -f boot.iso
