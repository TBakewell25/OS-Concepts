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

//like 'malloc()', but worse
void* mallocc(size_t space, node_t* heap){
	size_t netSize = space + sizeof(header_t*);
	if (heap->size >= netSize){
		void* base = heap;
		node_t* fd = memcpy(heap, heap+netSize, sizeof(node_t*));
	        
		header_t* newMemHead = (header_t*) base;
		newMemHead->magic = random();
		newMemHead->size = space;

		void* allocatedMem = base + netSize;
		return allocatedMem;		
	}
	if ((heap->size < netSize) && (heap->next != NULL)){
		heap = heap->next;
		void* allocatedMemory = mallocc(space, heap);
		return allocatedMemory;
	}
	else{
		return NULL;
	}

}
