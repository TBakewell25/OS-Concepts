/* Thomas Bakewell, University of Virginia
 * Implementation of free list
 * Based off OSTEP Chap 17
*/
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
void* mallocc(size_t space, node_t* head){
	while (head->next == NULL){ //TODO: add linked list logic
		if (head->size >= space){
			head->size = head->size - (space + sizeof(node_t));
			
			void* allocatedSpace = mmap(head,space+sizeof(header_t), 
					PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
			void* returnedMem = allocatedSpace+8;
			
			header_t* ptr = allocatedSpace; //create header for new memory block
			ptr->size = space;
			ptr->magic = random();
			return returnedMem;
		}
		break;
	}
	return NULL;
}

int main(void){
	node_t* head = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);	
	head->size = 4096 - sizeof(node_t);
	head->next = NULL;
	
	int* test = (int*) mallocc(sizeof(int), head);
	
	if (test == NULL){
		printf("Malloc Failed\n");
		return -1;
	}

	int val = 11;
	test = &val;
	printf("Stored Value: %d\n", (*test));
	printf("Remaining Size = %d\n", head->size);
	
	header_t* header = (header_t*) test-8;
	printf("Magic: %d\n", header->magic);
	printf("size: %d\n", header->size);
	return 0;
}



