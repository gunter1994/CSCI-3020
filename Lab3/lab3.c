/*
 * Sudoku Validator for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <Samantha House, Nathaniel Yearwood, Hunter Thompson>
 * All rights reserved.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

//  macros and constants
#define BUFFER_LEN 256
#define NUM_THREADS 11

// global environment variables
int puzzle[9][9]; //stores the puzzle
int results[NUM_THREADS]; //stores results from each thread

// function declarations
void *checkRows();
void *checkCols();
void *checkBoxes(void *params);

struct thread_args {
    int row;
    int col;
};

int main(int argc, char *argv[])
{   
    FILE *fp;
    char *line = NULL;
    char *token;
    int i,row=-1,col=-1;
    pthread_t threads[NUM_THREADS];
    size_t len = 0;
    ssize_t read;

    /* read in input file puzzle.txt */ 
    fp = fopen(argv[1], "r");
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        row++;
        token = strtok(line, " \n");
        while( token != NULL ) {
            col++;
            puzzle[row][col] = token;
            token = strtok(NULL," \n");
        }
    }
    fclose(fp);

    // set up threads to for checking boxes
    struct thread_args args;
      /*
      [0][0], [0][3], [0][6],
      [3][0], [3][3], [3][6],
      [6][0], [6][3], [6][6]
     */

     args.row = 0;
    for(i = 0; i < NUM_THREADS-2; i++) {
        if(i%3 == 0) { args.row += 3; }
        args.col = 3*(i % 3);
        pthread_create(&threads[i], NULL, checkBoxes, &args);
    }

    // set up thread for checking rows
    pthread_create(&threads[0], NULL, checkRows, NULL);

    // set up thread for checking columns
    pthread_create(&threads[1], NULL, checkCols, NULL);

   
    pthread_exit(NULL);
    return 0;
}

// check if row contains numbers 1-9
void *checkRows() {

}

// check if column contains numbers 1-9
void *checkCols() {

}

// check if box contains numbers 1-9
void *checkBoxes(void *params) {
    
}

