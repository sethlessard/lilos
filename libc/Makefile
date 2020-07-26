
CC = gcc
VERSION = 1000
SRCS = ${wildcard stdio/*.c} \
	   ${wildcard stdlib/*.c} \
	   ${wildcard string/*.c}
OBJS= ${SRCS:.c=.o}
WARN    = -W -Wall -Wstrict-prototypes -Wmissing-prototypes
CFLAGS  = -O2 -nostdinc ${WARN}

all: ${OBJS}
	
%.o: %.c
	gcc -m32 -Iinclude/ ${CFLAGS} -c -o $@ $^

.PHONY: clean
clean:
	rm -f ${OBJS}
	rm -f *.o
