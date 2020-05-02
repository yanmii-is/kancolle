# Kancolle
A battleship game made in C.

## Compiling
Compilation is done through `make` <br>
Alternatively, you can manually compile with `gcc -std=c99 -Wall -Werror -o kancolle main.c game.c board.c boat.c log.c utils.c config.c`

## Tests
`kancolle` comes with 3 default input tests <br>
Run all of them at once with `make -s test` <br>
Alternatively, you can manually run tests with `./kancolle < test_file.txt` and use `> /dev/null &> /dev/null` if you want to ignore stdout and stderr.

**random_b20_b11111.txt**: Board size 20 with 1 boat of each type. Random boat allocation. Attacks are done through naive bruteforce of the matrix from (0,0) to (19,19).

**random_b20_b33333.txt**: Board size 20 with 3 boats of each type. Random boat allocation. Attacks are done through naive bruteforce of the matrix from (0,0) to (19,19).

**random_b40_b99999.txt**: Board size 40 with 9 boats of each type. Random boat allocation. Attacks are done through naive bruteforce of the matrix from (0,0) to (39,39).

## Settings
Game settings are dynamic and can be changed in run-time prior to starting a new game. <br>
- ``LOGGING`` - Enables logging to stderr
- ``CLEAR_SCREEN`` - Enables screen clearing when appropriate
- ``REPLAY_ON_HIT`` - Allows a player to attack again if they hit a boat
