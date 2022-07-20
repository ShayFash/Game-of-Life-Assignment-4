# Game-of-Life-Assignment-4
What is Conway's Game of Life:

It is a famous simulation that can create thriving ”ecosystems” from simple binary grids of cells. You begin with an initial configuration of a grid of cells, which may be alive or dead. When simulating the game, time moves forward in a series of discrete steps. At each step, the new condition (alive or dead) of each cell is calculated before updating the entire board. The condition of each cell is calculated based on the number of neighbours that it has. Each cell has up to 8 neighbours: up, down, left, right, and the four diagonals. In this program, the grid is finite( 30 x 50 ): it does not loop. 

The rules for cells are as follows:
• If a cell is currently dead, and it has exactly 3 living neighbours, it will be alive in the next time step.
• if a cell is currently alive and has fewer than 2 living neighbours, it will die in in the next time step from loneliness.
1
• If a cell is currently alive and has 2 or 3 living neighbours, it will be alive in the next time step.
• If a cell is currently alive and has 4 or more living neighbours, it will die in the next time step from overcrowding.



How to run the program:

[Step 1] Open command prompt or terminal

[Step 2] Run command "make clean"

[Step 3] Run command "make"

[Step 4] Run command "make testRunner"

At this point you will see two executable files naming program and testRunner

[Optional Step] Run command "./testRunner"

This program will try to run tests to blank, block, blinker and glider grids by reading from the provided input and output text files.

[Step 5] Run the program by running this command "./program [FILENAME] [NUMBER_O_ITERATIONS]" or "./program -p [FILENAME] [NUMBER_O_ITERATIONS]"

FILENAME is the name of your text file for example "input_blank.txt" whereas NUMBER_O_ITERATIONS is the number of times you want the game to proceed by iterating to its next state.