/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void push(node_t *tail, resources res, int time)
{
	node_t *current = tail;
	node_t *temp;
	temp = malloc(sizeof(node_t));
	temp->res = res;
	temp->time = time;
	current->next = temp;
	*tail = *temp;
}

node_t *pop(node_t *head)
{
	node_t *temp = head;
	head = head->next;
	temp->next = NULL;
	return temp;
}
