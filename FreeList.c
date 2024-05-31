/* Thomas Bakewell, University of Virginia
 * Implementation of free list
 * Based off OSTEP Chap 17
*/
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct __node_t {
	int size;
	struct __node_t *next;
} node_t;

typedef struct {
	int size;
	int magic;
} header_t;

void* mallocc(size_t space, node_t* head){
	while (head->next == NULL){
		if (head->size >= space){
			head->size = head->size - (space + sizeof(node_t));
			
			void* allocatedSpace = mmap(head,space+sizeof(header_t), 
					PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
			header_t* ptr =  (&allocatedSpace) -1;
			ptr->size = space+sizeof(node_t);
			ptr->magic = random();
			return allocatedSpace;
		}
		break;
	}
	return NULL;
}

int main(void){
	node_t* head = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);	head->size = 4096 - sizeof(node_t);
	head->next = NULL;
	
	int* test = (int*) mallocc(10*sizeof(int), head);
	
	if (test == NULL){
		printf("Malloc Failed\n");
		return -1;
	}

	int val = 5;
	test = &val;
	//printf("%d", (*test));
	//printf("Remaining Size = %d\n", head->size);
	
	header_t* header = (header_t*) test -1;
	//printf("%d\n", header->magic);
	return 0;
}



