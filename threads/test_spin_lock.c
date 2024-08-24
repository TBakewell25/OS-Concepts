#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "lock.h"

struct args{
	int* counter; 
	void* mutex;
};
	

void* count_func(void* args){
	int* counter = ((struct args*)args)->counter;
	struct lock* mutex = ((struct args*)args)->mutex;

	int threshold = 1000, lcounter = 0, i;
	
	while ((*counter) < 1000000){
		for (i=0; i < threshold; i++){
			lcounter++;
			//printf("%d", lcounter);
			}
		
		acquire_lock(mutex);
		if (*counter < 1000000){
			*counter = ((*counter) + lcounter);
		}
		release_lock(mutex);
		
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
	
	
	pthread_create(&thread1, NULL, &count_func, args);	
	pthread_create(&thread2, NULL, &count_func, args);

	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Final count: %d\n", (*(args->counter)));
	return 0;
}


