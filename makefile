CC=gcc
CFLAGS=-Wall -Wextra -g
#CPPFLAGS=
#LDFLAGS=
LDLIBS= -lm

all: a.out
	@echo 'compilation finished'
a.out: term.h marc.h term.o marc.o main.o
	${CC} ${CFLAGS} ${LDLIBS} term.o marc.o main.o -o toroid.out
clean:
	rm -f *.out *.o
.PHONY: all clean
