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
#include <string.h>

//  macros and constants
#define BUFFER_LEN 256

// global environment variables
int puzzle[9][9]; //stores the puzzle
int results[11]; //stores results from each thread

int main(int argc, char *argv[])
{   
    FILE *fp;
    char *line = NULL;
    char *token;
    int row=-1,col=-1;
    char buffer[BUFFER_LEN];
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
    return 0;
}

