#ifndef BIT_TEST_H
#define BIT_TEST_H

int atomic_bit_test(int mutex, int bit){
	int val = (mutex>>bit)&0x00000001;
	if (val == 0){
		return 0;
	}
	return 1;
}

void atomic_increment(int* mutex){
	*mutex = *mutex | 0x80000000;
	}

void atomic_decrement(int* mutex){
	*mutex = (*mutex << 1) >> 1;
	}

int atomic_add_zero(int* mutex, int val){
	*mutex = *mutex + val;
	return *mutex;
	}	

#endif
