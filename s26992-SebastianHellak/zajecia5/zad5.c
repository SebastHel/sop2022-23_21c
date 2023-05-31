#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int i;
	pid_t pMain = getpid();

	for(i = 0; i < 100; i++){
		
		pMain  = fork();
		if(pMain == 0){
			printf("PID: %d\t PPID: %d\n", getpid(), getppid());
			exit(0);
		}
	} 
	
	if(pMain == getpid()){
		waitpid(-1,NULL,0);
	}
	return 0;
}
