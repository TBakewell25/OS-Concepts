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
	head->size = size - sizeof(node_t*);
	head->next = NULL;
	return head;
}

int main(void){
	heap = allocateHeap(4096);
	int* test = (int*) mallocc(sizeof(int));
	char* test2 = (char*) mallocc(sizeof(char));
	if (test == NULL){
		printf("Malloc Failed\n");
		return -1;
	}

	freed(test);
	freed(test2);

	return 0;
}



