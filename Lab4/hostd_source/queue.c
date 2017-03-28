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

node_t *push(node_t *tail, resources res, int time)
{
	node_t *current = tail;
	node_t *temp;
	temp = malloc(sizeof(node_t));
	temp->res = res;
	temp->procTime = time;
	current->next = (struct node_t *)temp;
	*tail = *temp;
	return temp;
}

node_t *pop(node_t *head)
{
	node_t *temp = head;
	head = (node_t *)head->next;
	temp->next = NULL;
	return temp;
}
