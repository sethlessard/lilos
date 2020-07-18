
CC = gcc
VERSION = 1000
PROG = kernel-${VERSION}
SRCS = ${wildcard src/driver/keyboard/*.c} \
	   ${wildcard src/driver/screen/*.c} \
	   ${wildcard src/idt/*.c} \
	   ${wildcard src/stdlib/*.c} \
	   ${wildcard src/*.c }
OBJS = ${SRCS:.c=.o}
WARN    := -W -Wall -Wstrict-prototypes -Wmissing-prototypes
CFLAGS  := -ffreestanding -O2 -DMODULE -D__KERNEL__ ${WARN}

all: ${PROG}

boot.o:
	nasm -f elf32 boot.asm -o boot.o
	
%.o: %.c
	gcc -m32 ${CFLAGS} -c -o $@ $^

${PROG}: boot.o ${OBJS}
	ld -m elf_i386 -T link.ld -o ${PROG} boot.o ${OBJS}

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
	rm -f ${OBJS}
	rm -f *.o
	rm -f ${PROG}
