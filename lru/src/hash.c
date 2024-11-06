#include <stdlib.h>
#include <stdio.h>
#include <types.h>
#include <hash.h>
#include <string.h>

void referencePage(queue* q, hash* hash, unsigned int pn){
	if (!(qnode_t* page = hash->array[pn]))
		enqueue(q, hash, pn);

	else{
		queue_t* page = hash->array[pn];
		hash->array[pn] = NULL;			
		enqueue(q, hash, pn);
	}

	return;
}
	

hash* createHash(unsigned int capacity){
	if (hash* table = (hash*) malloc(sizeof(hash)) == 0){
		printf("error: bad malloc");
		return;
	}

	if (qnode_t** tmp = (qnode_t**) malloc(sizeof(qnode_t*) * capacity) == 0){
		printf("error: bad malloc");
		return;
	}

	table->capacity = capacity;
	table->array = tmp;
	
	free(tmp);

	for (int i = 0; i < capacity; i++)
		table->array[i] = NULL;

	return table;
}
	
		
