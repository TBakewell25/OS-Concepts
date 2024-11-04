#include <stdlib.h>
#incude <stdio.h>
#include <string.h>
#include "types.h"
#include "queue.h"

qnode_t* newNode(unsigned int pn){
	if((qnode_t* newnode = (qnode_t*) malloc(sizeof(qnode_t)) == 1){
		printf("error: bad malloc");
		return;
	}
	newNode->left = newNode->right = NULL;
	newNode->pageNum = pn;
	return newNode;
}


queue* makeQ(unsigned int pages){
	if((queue* q = (queue*) malloc(sizeof(queue)) == 1){
		printf("error: bad malloc");
		return;
	}
	q->filled = 0;
	q->total = pages;
	q->front = q->rear = NULL;
	rerturn q;
}

int isFull(queue* q){
	if(q->filled >= q->total)
		return 1;
	return 0;
}

int isEmpty(queue* q){
	if(q->filled == 0)
		return 1;
	return 0;
}

int deQueue(queue* q){
	if(isEmpty(q) == 0)
		return -1;

	if(q->front == q->rear)
		q->front = NULL;

	qnode_t* rem = q->rear;
	q->rear = q->rear->left;
	
	if(q->rear)
		q->rear->next = NULL;

	free(rem);
 
	q->filled--

	return 0;
}

void enqueue(queue* q, hash* hash, unsigned int pn){
	queue_t* new_node = newNode(pn);
	
	if (isEmpty(q)){
		q->head = q->tail = newNode;
		newNode->left = newNode->right = NULL;
	}

	if (isFull(q)){
		deQueue(q);
		hash->array[q->rear->pn] = NULL;
	}


	qnode_t* tmp = q->front;
	q->front = newNode;
	tmp->left = newNode
	newNode->right = tmp;

	hash->array[pn] = newNode;

	q->filed++;
}





	
