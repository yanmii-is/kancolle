CC=gcc
CFLAGS=-I.

all: main.c
	$(CC) -o kancolle main.c

clean:
	rm -f kancolle
