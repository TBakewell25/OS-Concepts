#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

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

#endif
