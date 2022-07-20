#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/// returns value at index of grid
int valueAt(int r, int c, char** grid, int rows, int colums);

/// calculates alive neighbours of item at index of grid
int neighboursAt(int r, int c, char** grid, int rows, int colums);

/// prints grid to console
void print(char ** grid, int rows, int colums);

/// debug print for testing
void debugPrint(char ** grid, int rows, int colums);

/// iterates game to next step
char ** iterate(char ** grid, int rows, int colums);

/// generates test grid
char ** generateTestGrid(int rows, int colums);

/// removes extension .txt from filename
char * removeExtension(char * str);

/// removes substring from filename
char * removeSubString(char *str, const char *sub);

/// writes current state of grid to file
void writStateToFile(char ** grid, int rows, int colums, int iteration, const char* filename);

/// simulates N iterations of game and saves state to file at the end
void simulate(char ** grid, int N, int rows, int colums, bool pflag, const char* filename);

/// reads state from file
char ** readStateFromFile(const char* filename);

/// checks if file is present and readable
int isValidFile(const char* filename);

#endif /* game_h */
