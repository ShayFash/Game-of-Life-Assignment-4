#include "game.h"

const int ROWS      = 30;
const int COLUMS    = 50;
const char DEAD     = ' ';
const char ALIVE    = '*';

int valueAt(int r, int c, char** grid, int rows, int colums) {
    if ((r>=0 && r<rows && c>=0 && c<colums) == 0) return 0;        // sanity check if passed row and colum indices are in bounds
    if (grid[r][c] == ALIVE) {
        return 1;                                                   // return 1 if alive
    } else {
        return 0;                                                   // return 0 if dead
    }
}


int neighboursAt(int r, int c, char** grid, int rows, int colums) {
    if (grid == NULL) return 0;                                     // sanity null check
    if ((r>=0 && r<rows && c>=0 && c<colums) == 0) return 0;        // sanity check if passed rows and column indeices are in bounds
    
    int neighbours = 0;
    
    neighbours += valueAt(r-1, c-1, grid, rows, colums);            // adds if r-1 c-1 is alive
    neighbours += valueAt(r-1, c,   grid, rows, colums);            // adds if r-1 c is alive
    neighbours += valueAt(r-1, c+1, grid, rows, colums);            // adds if r-1 c+1 is alive
    neighbours += valueAt(r,   c-1, grid, rows, colums);            // adds if r c-1 is alive
    neighbours += valueAt(r,   c+1, grid, rows, colums);            // adds if r c+1 is alive
    neighbours += valueAt(r+1, c-1, grid, rows, colums);            // adds if r+1 c-1 is alive
    neighbours += valueAt(r+1, c,   grid, rows, colums);            // adds if r+1 c is alive
    neighbours += valueAt(r+1, c+1, grid, rows, colums);            // adds if r+1 c+1 is alive
    
    return neighbours;
}

void print(char ** grid, int rows, int colums) {
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<colums; j++) {
            printf("%c", grid[i][j]);                               // prints character at ij index of grid
            if (j == colums-1) printf("\n");                        // prints endline after each row iteration
        }
    }
}


void debugPrint(char ** grid, int rows, int colums) {
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<colums; j++) {
            printf("%d%d %c",i,j,grid[i][j]);
            if (j == colums-1) printf("\n");
        }
    }
}

char ** iterate(char ** grid, int rows, int colums) {
    char newGrid[rows][colums];                                                     // temporary new grid
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<colums; j++) {
            int neighbours      = neighboursAt(i, j, grid, rows, colums);           // alive neighbours at ij index
            char resultStatus   = DEAD;                                             // default value is dead
            if (grid[i][j] == DEAD ) {
                if (neighbours == 3) resultStatus = ALIVE;                          // ij is dead but has 3 alive neighbours
            } else if (grid[i][j] == ALIVE ){
                if (neighbours == 2 || neighbours == 3) resultStatus = ALIVE;       // ij is alive and has two or three alive neighbours
            }
            newGrid[i][j] = resultStatus;                                           // put the result at ij of temporary grid
        }
    }
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<colums; j++) grid[i][j] = newGrid[i][j];                  // copy temorary grid to orignial grid
    }
    return grid;
}


char ** generateTestGrid(int rows, int colums) {                                    // generates a test blinker grid
    char ** grid = (char **) malloc(rows * sizeof(char *));
    for (int i=0; i<rows; i++)
        grid[i] = (char *) malloc(colums * sizeof(char));
    
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<colums; j++) {
            grid[i][j] = DEAD;
        }
    }
    grid[5][5] = ALIVE;
    grid[5][6] = ALIVE;
    grid[5][7] = ALIVE;
    return grid;
}

char * removeExtension(char* str) {
    char *retstr;
    char *lastdot;
    if (str == NULL) return NULL;
    if ((retstr = malloc (strlen (str) + 1)) == NULL) return NULL;
    strcpy (retstr, str);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL) *lastdot = '\0';               // null terminate where . is found
    return retstr;
}

char * removeSubString(char *str, const char *sub) {    // remove substring from filename
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

void writStateToFile(char ** grid, int rows, int colums, int iteration, const char* filename) {
    char *suffix = malloc(strlen("_output_.txt") + sizeof(iteration));
    sprintf(suffix, "_output_%d.txt",iteration);
    char *_filename = malloc(strlen(filename)+strlen(suffix));
    memcpy(_filename, filename, strlen(filename));
    
    _filename = removeExtension(_filename);                     // remove .txt  extension from filename
    _filename = removeSubString(_filename, "input_");           // remove input_ from filename
    strcat(_filename, suffix);                                  // append _output_IterationCount.text at the end
    
    FILE *file = fopen(_filename, "w");                         // open file with write permissions
    if(file == NULL)
    {
        printf("Error while creating the file.\n");
        exit(1);
    }
    for (int i=0; i<rows; i++) {
        for (int j=0; j<colums; j++) {
            char c = grid[i][j];
            fputc(c, file);                                     // put char at ij of grid to file
            if(j == colums-1) {
                fputc('\n', file);                              // put endline after each row iteration
            }
        }
    }
    fclose(file);
}

void simulate(char ** grid, int N, int rows, int colums, bool pflag, const char* filename) {
    for (int i=0; i<N; i++) {
        iterate(grid, rows, colums);                            // interates to next state
        printf("State after iteration %d..\n",i+1);
        print(grid, rows, colums);                              // prints state of grid
        if(pflag){                                              // checks if pFlag was on
            writStateToFile(grid, rows, colums, i+1, filename); // writes current state to file
        }
    }
}

char ** readStateFromFile(const char* filename) {
    char ** grid = (char **) malloc(ROWS * sizeof(char *));
    for (int i=0; i<ROWS; i++)
        grid[i] = (char *) malloc(COLUMS * sizeof(char));
    
    FILE *file = fopen(filename, "r");                          // opens file with read permission
    if (file == NULL) {                                         // sanity null check
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLUMS; j++) {
            char c = fgetc(file);                               // gets character from file
            if (c == '\n') {                                    // checks if character was endline
                c = fgetc(file);                                // gets next character
            }
            grid[i][j] = c;                                     // puts char at ij index of grid
        }
    }
    fclose(file);                                               // closes file
    return grid;
}

int isValidFile(const char* filename) {
    FILE *file = fopen(filename, "r");                          // opens file with read permission
    if (file == NULL) {
        return 0;                                               // returns 0 if failure
    } else {
        fclose(file);                                           // closes file
        return 1;                                               // return 1 for success
    }
}
