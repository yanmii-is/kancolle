CC=gcc
CFLAGS=-std=c99 -Wall -Werror

all: main.c game.c boat.c log.c
	$(CC) $(CFLAGS) -o kancolle main.c game.c board.c boat.c log.c utils.c config.c

clean:
	rm -f kancolle

test:
	./kancolle < tests/random_b20_b11111.txt > /dev/null &> /dev/null
	echo "[TEST 1/3] Exit code: $$?";\
	./kancolle < tests/random_b20_b33333.txt > /dev/null &> /dev/null
	echo "[TEST 2/3] Exit code: $$?";\
	./kancolle < tests/random_b40_b99999.txt > /dev/null &> /dev/null
	echo "[TEST 3/3] Exit code: $$?";\
