CC=gcc
CFLAGS=-I.

all: main.c game.c boat.c log.c
	$(CC) -o kancolle main.c game.c board.c boat.c point.c log.c utils.c config.c

clean:
	rm -f kancolle
