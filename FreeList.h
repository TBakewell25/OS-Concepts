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
	int heapSize = heap->size;
	node_t* nextMem = heap->next;

	if (heap->size >= netSize){

		header_t* newHeader = (void*)heap;
		heap = (node_t*)((char*) heap + netSize);
		heap->size = heapSize - netSize;
		heap->next = nextMem;

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

void freed(void* mem){
	int freeSpace = heap->size;
	node_t* nextMem = heap->next;

	heap = mem - sizeof(header_t*);
	header_t* header = (header_t*) heap;

	heap->size = freeSpace + header->size + sizeof(header_t*);
	heap->next = nextMem;

}

