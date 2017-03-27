/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3
pthread mutex_t mutex;

struct thread_args {
    int customer;
    int res[] = {0};
};

// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];


// Define functions declared in banker.h here
bool request_res(int n_customer, int request[])
{

    pthread_mutex_lock(&mutex); 


    
    pthread_mutex_unlock(&mutex);
 
}

// Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{

    pthread_mutex_lock(&mutex); 


    
    pthread_mutex_unlock(&mutex);

}


int main(int argc, char *argv[])
{
    time_t t;
    srand((unsigned) time(&t));

    // Read in arguments from CLI, NUM_RESOURCES is the number of arguments 
     if ( argc != (NUM_RESOURCES + 1) ) { 
         printf("Incorrect number of resources passed.\n");
     } 
     else {
    // Allocate the available resources
         for(int i = 1; i <= NUM_RESOURCES; i++) {  
             available[i] = argv[i];
         }
     }

     // Initialize maximum array 
     for(int i = 0; i < NUM_CUSTOMERS; i++) {
         for(int j = 0; j < NUM_RESOURCES; j++) {
             maximum[i][j] = rand() % (available[j] + 1);
         }
     }

    // Initialize the pthreads, locks, mutexes, etc.
    pthread_t threads[NUM_CUSTOMERS];
    struct thread_args args[NUM_CUSTOMERS];
    
    // Run the threads and continually loop
    while(true) {
        for(int i = 0; i < NUM_CUSTOMERS; i++) {
            // The threads will request and then release random numbers of resources
            args[i].customer = i;
            args[i].
            if (pthread_create(&threads[i],NULL,request_res,(void *)i)) {

            }
        }
    }
  
    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
