/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, Hunter Thompson, Nathaniel Yearwood, Sam House
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"
#include <string.h>

// Put macros or constants here using #define

// Put global environment variables here

// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    
    // Load the dispatchlist
    char* dlist[10];
    char line[MEMORY];
    FILE * file;
    int i = 0;
    file = fopen("dispatchlist", "r");
    if (file) {
        while (fgets(line, sizeof(line), file)){
            dlist[i] = malloc(sizeof(line));
            strcpy(dlist[i],line);
            // printf("%s", line);
            i++;
        }
        fclose(file);
    }
    
    for (int j = 0; j < i; ++j){
        printf("%s", dlist[j]);
    }


    
	

    // Add each process structure instance to the job dispatch list queue
	
	

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}
