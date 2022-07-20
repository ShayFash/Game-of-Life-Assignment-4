#include <stdio.h>
#include "game.h"

bool sameGrids(char ** in, char ** out, int r, int c);

bool test(const char * inputFilename, const char * outputFilename, int n);

void runTest(const char* name, const char * in, const char * out, int n);

int main() {
    // test blank
    runTest("blank", "input_blank_grid.txt", "output_blank_grid_10.txt", 10);
    // test blinker
    runTest("blinker", "input_blinker.txt", "output_blinker_7.txt", 7);
    runTest("blinker", "input_blinker.txt", "output_blinker_20.txt", 20);
    // test block
    runTest("block", "input_block.txt", "output_block_100.txt", 100);
    // test glider
    runTest("block", "input_glider.txt", "output_glider_1.txt", 1);
    runTest("block", "input_glider.txt", "output_glider_2.txt", 2);
    runTest("block", "input_glider.txt", "output_glider_3.txt", 3);
    runTest("block", "input_glider.txt", "output_glider_4.txt", 4);

    printf("Testing ended!");
    return 0;
}

bool test(const char * inputFilename, const char * outputFilename, int n){
    if (isValidFile(inputFilename) == 0) {           // checks whether program was able to find and read the file or not
        printf("Error while opening the file %s. \n",inputFilename);
        return false;
    }
    if (isValidFile(outputFilename) == 0){           // checks whether program was able to find and read the file or not
        printf("Error while opening the file %s. \n",outputFilename);
        return false;
    }
    char ** inputGrid   = readStateFromFile(inputFilename); // creats 30x50 grid from provided file
    
    int rows=30,columns=50;
    
    for(int i=0; i<n; i++) iterate(inputGrid, rows, columns);
    
    char ** outputGrid  = readStateFromFile(outputFilename); // creats 30x50 grid from provided file
    
    return sameGrids(inputGrid, outputGrid, rows, columns);
}

void runTest(const char* name, const char * in, const char * out, int n) {
    printf("\nTesting %s for N = %d....\n", name, n);
    bool result = test(in, out, n);
    result ? printf("Success!") : printf("Failed!");
}

bool sameGrids(char ** in, char ** out, int r, int c) {
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(in[i][j] != out[i][j])  return false;
        }
    }
    return true;
}
