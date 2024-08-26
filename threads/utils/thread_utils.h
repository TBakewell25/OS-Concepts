#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

#include "mutex_lock.h"

void* create_threads(const int num, void* args, void* func){
	pthread_t* threads = malloc(sizeof(pthread_t) * num);
	for (int i = 0; i < num; i++){
		pthread_t newThread;	
		if (pthread_create(&newThread, NULL, func, args) ==1){
			printf("\nERROR: THREAD CREATION\n");
			return NULL;
		}
		threads[i] = newThread;	
	}
	return threads;
}

int destroy_threads(int num, pthread_t* threads, int* lock){
	mutex_lock(lock);
	for (int i = 0; i < num; i++){
		pthread_t thread = threads[i];	
		if (pthread_join(thread, NULL) == 1){
			printf("ERROR: JOINING THREAD 1");
			return 1;
		}
	}
	free(threads);
	mutex_unlock(lock);
	return 0;
}

#endif
