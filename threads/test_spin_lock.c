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

	int threshold = 10000, lcounter = 0, i;
	
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

void* create_threads(const int num, void* args){
	pthread_t* threads = malloc(sizeof(pthread_t) * num);
	for (int i = 0; i < num; i++){
		pthread_t newThread;	
		if (pthread_create(&newThread, NULL, &count_func, args) ==1){
			printf("\nERROR: THREAD CREATION\n");
			return NULL;
		}
		threads[i] = newThread;	
	}
	return threads;
}

int destroy_threads(int num, pthread_t* threads){
	for (int i = 0; i < num; i++){
		pthread_t thread = threads[i];	
		if (pthread_join(thread, NULL) == 1){
			printf("ERROR: JOINING THREAD 1");
			return 1;
		}
	}
	free(threads);
	return 0;
}
	

int main(int argc, char** argv){
	int thread_count = atoi(argv[argc-1]);
	struct args* args = (struct args*) malloc(sizeof(struct args));	

	int kill, gcounter;
	gcounter = 0;

	args->counter = &gcounter;
	args->mutex = init_lock();
	
	pthread_t* threads;
	if (!(threads = create_threads(thread_count, args))){
		printf("ERROR: CREATING THREADS");
		return 1;
	}	

	if (destroy_threads(thread_count, threads) == 1){
		printf("ERROR: JOINING THREADs");
		return 1;
	}

	printf("Final count: %d\n", (*(args->counter)));
	
	loseLock(args->mutex);
	free(args);

	return 0;
}


