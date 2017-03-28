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
#include <unistd.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3

pthread_mutex_t mutex;

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
    //temp arrays
    int res_avail[NUM_RESOURCES];
    int res_alloc[NUM_CUSTOMERS][NUM_RESOURCES];
    int res_need[NUM_CUSTOMERS][NUM_RESOURCES];

    for(int i = 0; i < NUM_CUSTOMERS; i++) {
        if( request[i] > need[n_customer][i] ) { return false; }
        else if( request[i] > available[i] ) { return false; }
        else {
            res_avail[i] = available[i] - request[i];
            res_alloc[n_customer][i] = allocation[n_customer][i] + request[i];
            res_need[n_customer][i] = need[n_customer][i] - request[i];
        }
    }

    int finish[NUM_CUSTOMERS] = {0};
    for(int j = 0; j < NUM_RESOURCES; j++) {
        while (true) {
            int check = 0;
            for(int i = 0; i < NUM_CUSTOMERS; i++) {
                if (finish[i] == 0 && res_need[i][j] <= res_avail[i] ) {
                    res_avail[i] += res_alloc[i][j];
                    finish[i] = 1;
                    check = 1;
                }
            }
            if( check = 0) { break; }
        }

        for(int i = 0; i < NUM_CUSTOMERS; i++) {
            if( finish[i] == 0 ) { return false; } 
        }
    }

    pthread_mutex_lock(&mutex); 

    for(int i = 0; i < NUM_RESOURCES; i++) {
        available[i] = res_avail[i];
        allocation[n_customer][i] = res_alloc[n_customer][i];
        need[n_customer][i] = res_need[n_customer][i];
    }

    pthread_mutex_unlock(&mutex);
 
}

// Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{

    pthread_mutex_lock(&mutex); 


    
    pthread_mutex_unlock(&mutex);

}


// The threads will request / release random numbers of resources
void *makeRequests(void *c) 
{
    int customer = (int)c;
    int res[NUM_RESOURCES];

    while(true) {
        sleep(2);
        int num = rand() % 2;
        if(num == 0) { //release

            for(int r = 0; r < NUM_RESOURCES; r++) {
                res[r] = rand() % (allocation[customer][r] + 1);
            }
            release_res(customer, res);

    
        } else { //request
            while (true) {
                for(int r = 0; r < NUM_RESOURCES; r++) {
                    res[r] = rand() % (maximum[customer][r] - allocation[customer][r] + 1);
                }
                if( request_res(customer, res) ) {
                    
                    break;
                } else {
                    sleep(1);
                }
            }
            
        }        
    }
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
    
    // Run the threads and continually loop
    for(int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_create(&threads[i],NULL,makeRequests,(void *)i);
    }

  

    return EXIT_SUCCESS;
}






   // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads