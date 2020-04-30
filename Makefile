CC=gcc
CFLAGS=-std=c99 -Wall -Werror

all: main.c game.c boat.c log.c
	$(CC) $(CFLAGS) -o kancolle main.c game.c board.c boat.c log.c utils.c config.c

clean:
	rm -f kancolle
