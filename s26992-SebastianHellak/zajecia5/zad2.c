#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	
	pid_t p = fork();
	switch (p){
		case -1:
			printf("Nie udało się utworzyć dziecka PID: %d\t PPID: %d\n",getpid(), getppid());
			break;
		case 0:
			printf("PID: %d\t PPID: %d\n", getpid(), getppid());
			break;
		default:
			wait(NULL);	
			printf("PID: %d\t PPID: %d\n", getpid(), getppid());
			break;
	}
	return 0;
}
