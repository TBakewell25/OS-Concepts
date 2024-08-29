#ifndef QUEUE_H
#define QUEUE_H
#include "types.h"

qnode_t* newNode(unsigned int pn);

queue* makeQ(unsigned int pages);

int isFull(queue* q);

int isEmpty(queue* q);

int deQueue(queue* q);

int enqueue(queue* q, hash* hash, unsigned int pn);

#endif
