/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Sam House, Hunter Thompson, Nathaniel Yearwood
 * All rights reserved.

   If your program hangs you may have a deadlock, otherwise you *may* have
   implemented the banker's algorithm correctly
   
   If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
   to just 2 and focus on getting the multithreading working for just two threads
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

    for(int i = 0; i < NUM_RESOURCES; i++) {
        if( request[i] > need[n_customer][i] ) { return false; }
        else if( request[i] > available[i] ) { return false; }
        else {
            res_avail[i] = available[i] - request[i];
            res_alloc[n_customer][i] = allocation[n_customer][i] + request[i];
            res_need[n_customer][i] = need[n_customer][i] - request[i];
        }
    }

    int finish[NUM_CUSTOMERS][NUM_RESOURCES] = {0};
    int cust_remain = NUM_CUSTOMERS;
    int check = 0;
    while(cust_remain > 0) {
        for (int i = 0; i < NUM_CUSTOMERS; i++) {
            for(int j = 0; j < NUM_RESOURCES; j++) {
                if (finish[i][j] == 0 && res_need[i][j] <= res_avail[j] ) {
                    res_avail[j] += res_alloc[i][j];
                    finish[i][j] = 1;
                    check = 1;
                }
            }
    
            int clear = 0;
            for (int k = 0; k < NUM_RESOURCES; k++) {
                if (finish[i][k] != 1) {
                    clear = 1;
                }
            }
            if (clear == 0) {
                cust_remain--;
            }
            clear = 0;  
        }
        if (check == 0) {
            return false;
        }
        check = 0;
    }

    pthread_mutex_lock(&mutex); 

    for(int i = 0; i < NUM_RESOURCES; i++) {
        available[i] = res_avail[i];
        allocation[n_customer][i] = res_alloc[n_customer][i];
        need[n_customer][i] = res_need[n_customer][i];
    }

    pthread_mutex_unlock(&mutex);
    return true;
}

// Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
    pthread_mutex_lock(&mutex); 

    for(int i = 0; i < NUM_RESOURCES; i++) {
        available[i] += release[i];
        allocation[n_customer][i] -= release[i];
        need[n_customer][i] += release[i];
    }
    
    pthread_mutex_unlock(&mutex);
    return true;
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

            for(int i = 0; i < NUM_RESOURCES; i++) {
                res[i] = rand() % (allocation[customer][i] + 1);
            }
            release_res(customer, res);
            printf("(%d,%d,%d) Customer%d released resources (%d,%d,%d)\n",res[0],res[1],res[2],customer,available[0],available[1],available[2]);
            fflush(stdout);
    
        } else { //request
            while (true) {
                   for(int r = 0; r < NUM_RESOURCES; r++) {
                    res[r] = rand() % (maximum[customer][r] + 1);
                }
                if( request_res(customer, res) ) { // something broke here because after customer receives resources, it prints a huge number for that resources
                    printf("Customer%d received resources (%d,%d,%d). Available: (%d,%d,%d)\n",customer,res[0],res[1],res[2],available[0],available[1],available[2]);
                    fflush(stdout);
                    break;
                } else {
                    printf("Customer%d denied resources (%d,%d,%d). Available: (%d,%d,%d)\n",customer, res[0],res[1],res[2],available[0],available[1],available[2]);
                    fflush(stdout);
                    sleep(1);
                }
            }
            
        }        
    }
    return 0;
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
         for(int i = 0; i < NUM_RESOURCES; i++) {  
             available[i] = atoi(argv[i]);
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

    for(int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(threads[i],NULL);
    }

    return EXIT_SUCCESS;
}
