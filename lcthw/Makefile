CFLAGS=-Wall -g

all: liblcthw.a

lcthw.o: lcthw.c
	gcc $(CFLAGS) -c lcthw.c
liblcthw.a: lcthw.o
	ar rcs liblcthw.a lcthw.o
clean:
	rm -f liblcthw.a lcthw.o
