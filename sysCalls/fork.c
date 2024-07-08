#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void childInfo(pid_t pid){
	if (pid < 0){
		printf("Fork call failed!");
	}
	if (pid == 0){
		printf("Child ID is: %d\n", (int) getpid());
		printf("Parent ID is: %d\n", (int) getppid());
		sleep(5);
	}
}
int main(int argc, char** argv){
	pid_t pid = fork(); //fork a chid from the parent
		
	if (pid > 0){ //if the current process is not the child
		pid_t pid = fork(); //fork a new child from the parent
		childInfo(pid); //get info for the freshly forked process
		wait(&pid); //wait for second child to complete
		printf("Child process complete\n");
		}
	else{
		childInfo(pid); //if in the child process get info

	}		
	return 0;
}
