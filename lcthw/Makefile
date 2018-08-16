CFLAGS=-Wall -g

all: liblcthw.a

ex1.o: ex1.c
	gcc $(CFLAGS) -c ex1.c
liblcthw.a: ex1.o
	ar rcs liblcthw.a ex1.o
clean:
	rm -f liblcthw.a ex1.o
