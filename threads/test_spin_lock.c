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

	int threshold = 500, lcounter = 0, i;

	
	while ((*counter) < 1000 && lcounter < threshold){
		for (i=0; i < threshold; i++){
			lcounter++;
			//printf("%d", lcounter);
			}
		acquire_lock(mutex);
		counter = (counter + lcounter);
		release_lock(mutex);
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

	printf("Final count: %d", (*(args->counter)));
	return 0;
}


