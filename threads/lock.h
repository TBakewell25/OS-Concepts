#ifndef locks_h
#define locks_h

struct lock{
	int lock;
	//int condition;
};

struct lock* init_lock(){
	struct lock* newLock = (struct lock*) malloc(sizeof(struct lock));
	newLock->lock = 0;
	return newLock;
}

int loseLock(struct lock* mutex){
	free(mutex);
	return 0;
}

int acquire_lock(struct lock* mutex){
	while (mutex->lock != 0){
		//spin
	}
	mutex->lock = 1;
	
	return 0;
}

int release_lock(struct lock* mutex){
	mutex->lock = 0;
	return 0;
}
#endif
