#ifndef locks_h
#define locks_h

struct lock{
	int lock;
	//int condition;
};

//implementation from OSTEP
int test_and_set(int* lock, int new){
	int old = *lock; //assign the previous lock value to old
	*lock = new; //update lock
	return old; //return the original value
}
//increases atomicity
	

struct lock* init_lock(){
	struct lock* newLock = (struct lock*) malloc(sizeof(struct lock));
	newLock->lock = 0;
	return newLock;
}

void loseLock(struct lock* mutex){
	free(mutex);
}

void acquire_lock(struct lock* mutex){
	while (test_and_set(&mutex->lock, 1) == 1){ //test and set
		//spin
	}
}

void release_lock(struct lock* mutex){
	mutex->lock = 0;
}

// for glibc mutex implementation

void futex_wait(int* mutex, int expected){
	while(*mutex == expected)
		; //spin
	return;
	}

void futex_wake(int* mutex){
	*mutex = 0;
}	
#endif
