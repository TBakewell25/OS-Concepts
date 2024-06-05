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
		void* base = heap;
		printf("Initial heap: %p\n", heap);
		heap = (node_t*) memcpy(heap+netSize, heap, sizeof(node_t*));
	        printf("Second heap: %p\n", heap);
		header_t* newMemHead = (header_t*) base;
		newMemHead->magic = random();
		newMemHead->size = space;

		void* allocatedMem = base + netSize;
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
	header_t* memHeader = (void*) header - 12;
	size_t memSize = memHeader->size;
	//memset(memHeader, 0, memSize + sizeof(header_t*));
	
	node_t* fd = memcpy(heap, memHeader, sizeof(node_t*));
	fd->size = fd->size + memSize+sizeof(header_t*);
	printf("%d\n", fd->size);
	return;
}

