#ifndef MUTEX_H
#define MUTEX_H

#include <stdlib.h>
#include <stdio.h>
#include "bit_test.h"
#include "lock.h"

/*
Basic implementation of GNU Libc mutexes
based on OSTEP
*/

void mutex_lock(int* mutex){
	int k;
	if (atomic_bit_test(*mutex, 31) == 0) //if the lock is unlocked
		atomic_increment(mutex); //modified to lock the lock
		return;
	//atomic_increment(mutex); //otherwise increment the lock
	//NOTE: exists in OSTEP implementation, moved to line 17, now it works
	while(1){
		if (atomic_bit_test(*mutex, 31) == 0){ //test again if it is unlocked
			atomic_increment(mutex); //same as above
			//atomic_decrement(mutex); 
			return;
		}
		k = *mutex;
		if (k >= 0)
			continue;
		futex_wait(mutex, k); //wait for lock queue

	}
}	

void mutex_unlock(int* mutex){
	if (atomic_add_zero(mutex, 0x80000000)) //add 0x800..., 0 out 32 bit int
		return;
	futex_wake(mutex); //wake waiting threads
	}

#endif
