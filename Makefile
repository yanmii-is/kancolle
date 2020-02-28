CC=gcc
CFLAGS=-I.

all: main.c game.c
	$(CC) -o kancolle main.c game.c

clean:
	rm -f kancolle
