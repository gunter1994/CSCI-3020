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
    pthread_create(&threads[thread], NULL, checkRows, (void *)thread);

    // set up thread for checking columns
    thread = 10;
    pthread_create(&threads[thread], NULL, checkCols, (void *)thread);
    
    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(&threads[i], NULL); 
    }

    for(i=0; i<NUM_THREADS; i++) {
        if(results[i] == 0) {
            printf("invalid\n");
            return 0;
        }
    }
   printf("valid");
   return 0;
}

// check if rows contain numbers 1-9
void *checkRows(void *t) {
    int thread = (int)t;
    int numTest[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //defaults values to false
    
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) { //checks each row for every number
            if(puzzle[i][j] != 0) {
                numTest[puzzle[i][j] -1] ++;
            }
        }
        for(int k = 0; k < 9; k++) {
            if(numTest[k] > 1) {  //if one num occurs twice, sets result
                results[thread] = 0;
                printf("Rows failed"); //DELETE THIS
                pthread_exit(NULL);
            } else { //sets rest to false again
                numTest[k] = 0;
            }
        }
    }
    results[thread] = 1;
    pthread_exit(NULL);
}

// check if columns contain numbers 1-9
void *checkCols(void *t) {
    int thread = (int)t;
    int numTest[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //defaults values to false
    
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) { //checks each row for every number
            if(puzzle[j][i] != 0) {
                numTest[puzzle[j][i] -1] ++;
            }
        }
        for(int k = 0; k < 9; k++) {
            if(numTest[k] > 1) {  //if one num occurs twice, sets result
                results[thread] = 0;
                printf("Columns failed"); //DELETE THIS
                pthread_exit(NULL);
            } else { //sets rest to false again
                numTest[k] = 0;
            }
        }
    }
    results[thread] = 1;
    pthread_exit(NULL);
}

// check if box contains numbers 1-9
void *checkBoxes(void *arguments) {
	struct thread_args *args = (struct thread_args *)arguments;
    int numTest[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //defaults values to false
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) { //checks each box for every number
            if(puzzle[i * args->row][j * args->col] != 0) {
                numTest[puzzle[i * args->row][j * args->col] -1] ++;
            }
        }
        
    }
    for(int k = 0; k < 9; k++) {
            if(numTest[k] > 1) {  //if one num occurs twice, sets result
                results[args->thread] = 0;
                printf("Boxes failed"); //DELETE THIS
                pthread_exit(NULL);
            }
        }
    results[args->thread] = 1;
    pthread_exit(NULL);
}


