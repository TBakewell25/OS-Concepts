#ifndef TYPES_H
#define TYPES_H

typedef struct qnode_t{  //queue node
	qnode_t* left, right;
	unsigned int pageNum;
}qnode_t;

typedef struct queue{
	unsigned int filled, total;
	qnode_t* front, rear;
}queue;

typedef struct hash{
	int capacity;
	qnode_t** array;
}hash;

#endif
