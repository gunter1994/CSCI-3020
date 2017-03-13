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
void *checkRows(void *thread);
void *checkCols(void *thread);
void *checkBoxes(void *params);

struct thread_args {
    int thread;
    int row;
    int col;
};

int main(int argc, char *argv[])
{   
    FILE *fp;
    char *line = NULL;
    char *token;
    int i,row=0,col=0;
    int thread;
    pthread_t threads[NUM_THREADS];
    size_t len = 0;
    ssize_t read;

    /* read in input file puzzle.txt */ 
    fp = fopen(argv[1], "r");
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        token = strtok(line, " ");
        while( token != NULL ) {
            puzzle[row][col] = atoi(token);
            token = strtok(NULL," \n");
            col++;
        }
        col = 0;
        row++;
    }
    fclose(fp);

    for (int i = 0; i < 9; i++) {
        printf("\nRow %i \n", i);
        for (int j = 0; j < 9; j++) {
            printf("%i ", puzzle[i][j]);
        }
    }

    // set up threads to for checking boxes
    struct thread_args args;
  
    args.row = 0;
    for(i = 0; i < NUM_THREADS-2; i++) {
        if(i%3 == 0) { args.row += 3; }
        args.thread = i;
        args.col = 3*(i % 3);
        pthread_create(&threads[i], NULL, checkBoxes, &args);
    }

    // set up thread for checking rows
    thread = 9;
    pthread_create(&threads[0], NULL, checkRows, (void *)thread);

    // set up thread for checking columns
    thread = 10;
    pthread_create(&threads[1], NULL, checkCols, (void *)thread);

    pthread_exit(NULL);
    return 0;
}

// check if rows contain numbers 1-9
void *checkRows(void *thread) {


}

// check if columns contain numbers 1-9
void *checkCols(void *thread) {
    _Bool numTest[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //defaults values to false
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) { //checks for every number
            numTest[puzzle[i][j]] = 1;
        }
        for(int k = 0; k < 9; k++) {
            if(numTest[k] != 1) {  //if one num wasnt found, returns, and sets result
                results[10] = 0;
                return thread;
            } else { //sets rest to false again
                numTest[k] = 0;
            }
        }
    }
    return thread;
}

// check if box contains numbers 1-9
void *checkBoxes(void *params) {
    
}

