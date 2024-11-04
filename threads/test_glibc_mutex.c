#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "utils/mutex_lock.h"
#include "utils/lock.h"
#include "utils/thread_utils.h"

struct args{
	int* mutex;
};
	
void* print_messages(void* args){
	struct args* lock_prim = (struct args*) args;
	mutex_lock(lock_prim->mutex);
	printf("\nThread has lock\n");
	mutex_unlock(lock_prim->mutex);
}

int main(int argc, char** argv){
	struct lock* basicLock = init_lock();
	
	int thread_count = 5;//atoi(argv[argc-1]);
	
	struct args* args = (struct args*) malloc (sizeof(struct args));	
	args->mutex = &(basicLock->lock);
	
	printf("Begin\n");
	pthread_t* threads = create_threads(thread_count, args, &print_messages, &(basicLock->lock));
	
	if (destroy_threads(thread_count, threads, &(basicLock->lock))){
		printf("ERROR: JOIN");
		return 1;
	}

	printf("\nEnd\n");
	free(args);
	return 0;
}
