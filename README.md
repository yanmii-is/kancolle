# Kancolle
<img src="https://images6.alphacoders.com/608/608732.jpg" width="256">

A battleship game made in C99
<br>
*Our fates are never sure, but no matter what, I’m happy to be a member of this fleet*


## Settings
Game settings are dynamic and can be changed in run-time prior to starting a new game. <br>
- ``LOGGING`` - Enables logging to stderr
- ``CLEAR_SCREEN`` - Enables screen clearing when appropriate
- ``REPLAY_ON_HIT`` - Allows a player to attack again if they hit a boat
- ``SHOW_BOAT_TYPE_ON_HIT`` - Allows a player to see the boat type on hit

## Compiling
Compilation is done through `make` <br>
Alternatively, you can manually compile with `gcc -std=c99 -Wall -Werror -o kancolle main.c game.c board.c boat.c log.c utils.c config.c`

## Running
`./kancolle` on your favorite console window

## Structure
Simplified program flow diagrams are included as .drawio and .png: `diagram.drawio` and `diagram.png` <br>
The program has the following classes:
- main: Interacts with the game's backend, contains the I/O code.
- game: Contains code relative to the game strcuture. A game structure contains two boards and the game state.
- board: Contains code relative to the board structure. A board structure contains height, width, amount of boats, a cell matrix and list of boats.
- boat: Contains code relative to the boat structure. A boat structure contains type, rotation, a bitmap matrix and life points.
- config: Contains game settings and their predefined values.
- log: Contains logging code.
- utils: Contains utilities for I/O.
- cell: Contains the cell structure.
- stdafx: Contains return_code values and typedef for 1 and 2 byte (un)signed types.

## Tests
There are 3 default input tests <br>
Run all of them at once with `make -s test` <br>
Alternatively, you can manually run tests with `./kancolle < test_file.txt` and use `> /dev/null &> /dev/null` if you want to ignore stdout and stderr.

- **random_b20_b11111.txt**: Board size 20 with 1 boat of each type. Random boat allocation. Attacks are done through naive bruteforce of the matrix from (0,0) to (19,19).
- **random_b20_b33333.txt**: Board size 20 with 3 boats of each type. Random boat allocation. Attacks are done through naive bruteforce of the matrix from (0,0) to (19,19).
- **random_b40_b99999.txt**: Board size 40 with 9 boats of each type. Random boat allocation. Attacks are done through naive bruteforce of the matrix from (0,0) to (39,39).
