
CC = gcc
PROG = kernel
SRCS = ${wildcard src/driver/keyboard/*.c} \
	   ${wildcard src/driver/screen/*.c} \
	   ${wildcard src/idt/*.c} \
	   ${wildcard src/stdlib/*.c} \
	   ${wildcard src/*.c }
OBJS = ${SRCS:.c=.o}
WARN    := -W -Wall -Wstrict-prototypes -Wmissing-prototypes
CFLAGS  := -ffreestanding -O2 -DMODULE -D__KERNEL__ ${WARN}

all: kernel

boot.o:
	nasm -f elf32 boot.asm -o boot.o
	
%.o: %.c
	gcc -m32 ${CFLAGS} -c -o $@ $^

kernel: boot.o ${OBJS}
	ld -m elf_i386 -T link.ld -o kernel boot.o ${OBJS}

.PHONY: run
run: kernel
	qemu-system-i386 -kernel kernel

.PHONY: clean
clean:
	rm -f ${OBJS}
	rm -f *.o
	rm -f kernel
