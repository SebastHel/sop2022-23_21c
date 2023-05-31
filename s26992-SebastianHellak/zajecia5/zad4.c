#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int i; int Procesy = 50;
	for(i=0; i< Procesy i++){
		pid_t proces=0;
		proces = fork();
		printf("PID: %d\t PPID: %d\n", getpid(), getppid());		
		if(proces > 0){
			wait(NULL);
			break;
		}
	}
	return 0;
}
