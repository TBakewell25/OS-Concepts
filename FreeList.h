#/* Thomas Bakewell, University of Virginia
 * Implementation of free list
 * Based off OSTEP Chap 17
*/
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//struct for heap node
typedef struct __node_t {
	int size;
	struct __node_t *next;
} node_t;

//struct for memory block headers
typedef struct {
	int size;
	int magic;
} header_t;

node_t* heap;
//like 'malloc()', but worse
void* mallocc(size_t space){
	size_t netSize = space + sizeof(header_t*);
	if (heap->size >= netSize){

		header_t* newHeader = (void*)heap;
		heap = (node_t*)((char*) heap + netSize);
	
		void* allocatedMem =  newHeader + 1;

		newHeader->size = space;
		newHeader->magic = random();
		
		return allocatedMem;
	}
	if ((heap->size < netSize) && (heap->next != NULL)){
		heap = heap->next;
		void* allocatedMemory = mallocc(space);
		return allocatedMemory;
	}
	else{
		return NULL;
	}

}

void freed(void* header){
	heap = (node_t*) header - 1;
	header_t* memHeader = (header_t*)((char*)header -1);
/*
	header_t* memHeader = (header_t*) header - 1;
	size_t memSize = memHeader->size;
	
	node_t* fd = heap;
	fd->size = fd->size + memSize+sizeof(header_t*);
	printf("%d\n", fd->size);
	return;
*/
}

