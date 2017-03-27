/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#define MEMORY 1024

// Your linked list structure for your queue
typedef struct {
	int memory[MEMORY];
	int printers;
	int scanners;
	int modems;
	int cd_drives;
} resources;

typedef struct { 
    int time;
    resources res;
	struct node_t *next;
} node_t;

typedef struct {
	node_t head;
	node_t tail;	
} queue;

extern node_t* push(node_t *tail, resources res, int time);
extern node_t* pop(node_t *head);

#endif /* QUEUE_H_ */
