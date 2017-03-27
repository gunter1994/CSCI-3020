/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "queue.h"

// Define your utility functions here, you will likely need to add more...

int alloc_mem(resources res, int size)
{
	int chunk = 0;
	int index = 0;
	int check = 0;
	for (int i = 0; i < sizeof(res.memory)/sizeof(res.memory[0]); i++) {
		if(chunk == size) {
			check = 1;
			break;
		}
		if(res.memory[i] == 0) {
			chunk++;
		} else {
			chunk = 0;
		}
		index++;
	}
	if (check = 0) {
		return -1;
	}
	for (int j = index; j < index+size; j++) {
		res.memory[j] = 1;
	}
	return index;
}

free_mem(resources res, int index, int size)
{
	for (int i = index; i < index+size; i++) {
		res.memory[i] = 0;
	}
}
