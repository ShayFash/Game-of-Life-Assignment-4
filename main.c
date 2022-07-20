//
//  main.c
//  CG
//
//  Created by Sajjad  on 16/06/2019.
//  Copyright © 2019 TestProj. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "game.h"

int main(int argc, const char * argv[]) {
    int R=30, C=50, n=1;                    // default values for total rows, colums and number of iterations
    bool pFlag = false;                     // to support -p outputting to file after each iteration
    char * filename = NULL;                 // file name provided in arguments

    if (argc < 3) {                         // sanity check to make sure greater than 1 argument was passed along
        printf("Error. Need file name and number of steps.\n");
        exit(0);
    }
    if(strcmp(argv[1], "-p") == 0) {        // checks whether -p was the first argument or not
        pFlag = true;                       // turns pflag on
    }
    if(pFlag) {                             // checks if pflag was on
        if (argc < 4) {                     // sanity check to make sure that there that three arguemnts were passed along
            printf("Error. Required argument not passed.\n");
            exit(0);
        } else {
            filename = malloc(strlen(argv[2])+1);
            strcpy(filename, argv[2]);          // copies filename from second argument  of program
            n = atoi(argv[3]);                  // saves number of iterations from third argument
        }
    } else {
        filename = malloc(strlen(argv[1])+1);   // pflag was off
        strcpy(filename, argv[1]);              // copies filename from first argument  of program
        n = atoi(argv[2]);                      // saves number of iterations from second argument
    }

    if (filename == NULL) {                     // sanity null check
        printf("Filename not found.");
        exit(0);
    }

    if (isValidFile(filename) == 0) {           // checks whether program was able to find and read the file or not
        printf("Error while opening the file.\n");
        exit(0);
    }

    char ** grid = readStateFromFile(filename); // creats 30x50 grid from provided file

    print(grid, R, C);                          // prints initial state of grid
    
    simulate(grid, n, R, C, pFlag, filename);   // simulates the game iterations
    if(pFlag == false) {
        writStateToFile(grid, R, C, n, filename);
    }
    return 0;
}



