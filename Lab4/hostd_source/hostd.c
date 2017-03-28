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
            i++;
        }
        fclose(file);
    }
    
    

    // Add each process structure instance to the job dispatch list queue
    

    char *token;
    node_t job[10];
    for (int j = 0; j < i; ++j){
        token = strtok(dlist[j], ", ");
        job[j].arrival = atoi(token);

        token = strtok(NULL, ", ");
        job[j].priority = atoi(token);

        token = strtok(NULL, ", ");
        job[j].procTime = atoi(token);

        token = strtok(NULL, ", ");
        job[j].res.memory = atoi(token);

        token = strtok(NULL, ", ");
        job[j].res.printers = atoi(token);

        token = strtok(NULL, ", ");
        job[j].res.scanners = atoi(token);

        token = strtok(NULL, ", ");
        job[j].res.modems = atoi(token);

        token = strtok(NULL, ", ");
        job[j].res.cd_drives = atoi(token);
    }
	

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues
    int latest = 0;
    char *queueN[4] = { "RT", "P1", "P2", "P3" };

    for (int j = 0; j < i; j++) {
        if(job[j].arrival > latest) {
            latest = job[j].arrival;
        }
    }
    int timeStep = 0;
    queue rt;
    queue p1;
    queue p2;
    queue p3;
    while (true){
        printf("Time step %d\n", timeStep);
        for(int j = 0; j < i; j++) {
            if(job[j].arrival == timeStep) {
                printf("Process %d added to %s queue\n", (j+1), queueN[job[j].priority]);
            }
        }
        if (timeStep == latest) {
            break;
        }
        timeStep++;
    }

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}
