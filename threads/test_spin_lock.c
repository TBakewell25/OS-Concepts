#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "lock.h"

struct args{
	int* counter; 
	void* mutex;
}; //struct for args to pass to threads
	

void* count_func(void* args){ //threaded function to count
	int* counter = ((struct args*)args)->counter; 
	struct lock* mutex = ((struct args*)args)->mutex;

	int threshold = 7500, lcounter = 0, i;
	
	while ((*counter) < 1000000){ 
		for (i=0; i < threshold; i++){
			lcounter++;
			}
		
		acquire_lock(mutex); //acquire the lock
		if (*counter < 1000000){ //atomically update counter
			*counter = ((*counter) + lcounter);
		}
		release_lock(mutex); //release the lock
		
		lcounter = 0;
	}
	return NULL;
}	
	
int main(){
	pthread_t thread1, thread2;

	struct args* args = (struct args*) malloc(sizeof(struct args));	

	int gcounter = 0;
	args->counter = &gcounter;
	args->mutex = init_lock();
	
	
	if (pthread_create(&thread1, NULL, &count_func, args) ==1){
		printf("\nERROR: THREAD CREATION\n");
		return 1;
	}

	if (pthread_create(&thread2, NULL, &count_func, args) ==1){
		printf("\nERROR: THREAD CREATION\n");
		return 1;
	}
	
	if (pthread_join(thread1, NULL) == 1){
		printf("ERROR: JOINING THREAD 1");
		return 1;
	}	

	if (pthread_join(thread2, NULL) == 1){
		printf("ERROR: JOINING THREAD 2");
		return 1;
	}
	printf("Final count: %d\n", (*(args->counter)));
	return 0;
}


