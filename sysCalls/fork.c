#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char** argv){
	int newID = fork();
	if (newID < 0){
		printf("Fork call failed!");
		return -1;
	}
	if (newID == 0){
		printf("\nChild ID is: %d\n", (int) getpid());
		printf("Parent ID is: %d\n", (int) getppid());
	}
	return 0;
}
