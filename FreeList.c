/* Thomas Bakewell, University of Virginia
 * Implementation of free list
 * Based off OSTEP Chap 17
*/
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "FreeList.h"

node_t*  allocateHeap(const int size){
	node_t* head = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);	
	head->size = size - sizeof(node_t);
	head->next = NULL;
	return head;
}

int main(void){
	node_t* head = allocateHeap(4096);
	int* test = (int*) mallocc(sizeof(int), head);
	if (test == NULL){
		printf("Malloc Failed\n");
		return -1;
	}

	int val = 11;
	*test = val;
	printf("Stored Value: %d\n", (*test));
	printf("Remaining Size = %d\n", head->size);

	printf("%d\n", sizeof(header_t*));
	test = test - sizeof(header_t*);
	header_t* header = (header_t*) test;
	printf("Magic: %d\n", header->magic);
	printf("size: %d\n", header->size);
	return 0;
}



