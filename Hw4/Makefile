CC=gcc
CFLAGS=-c -Wall -g
LASTNAME=Hammersley

all: hw4

hw4: mem.o main.o
	$(CC) -g mem.o main.o -o hw4 -lm

mem.o: mem.c mem.h
	$(CC) $(CFLAGS) mem.c

main.o: main.c mem.h
	$(CC) $(CFLAGS) main.c

clean:
	/bin/rm -f hw4 mem.o main.o $(LASTNAME).tar.gz

run:
	./hw4 1000 100 10 1235

tarball:
	tar -czvf $(LASTNAME).tar.gz main.c mem.c mem.h Makefile
