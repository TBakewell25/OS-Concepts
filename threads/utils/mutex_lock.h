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
	if (atomic_bit_test(*mutex, 31) == 0)
		return;
	atomic_increment(mutex);
	while(1){
		if (atomic_bit_test(*mutex, 31) == 0){
			atomic_decrement(mutex);
			return;
		}
		k = *mutex
		if (k >= 0)
			continue;
		futex_wait(mutex, k);

	}
}	

void mutex_unlock(int* mutex){
	if (atomic_add_zero(mutex, 0x80000000))
		return;
	futex_wake(mutex);
	}

#endif
