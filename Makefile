CC=gcc
CFLAGS=-I.

all: main.c game.c
	$(CC) -o kancolle main.c game.c board.c boat.c

clean:
	rm -f kancolle
