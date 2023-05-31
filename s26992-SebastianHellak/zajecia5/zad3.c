#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	pid_t proc = fork();
	int i, int g = atoi(argv[1])

	switch (proc){
		case -1:
			printf("%d Nie stworzono dziecka!\n", getpid());
			break;
		case 0:
			
			printf("Proces-D PID: %d\t PPID: %d\n", getpid(), getppid());
			for(i=1; i<g; i+=2){
				printf("Liczba: %d \n", i);
			}
			printf("Proces-D PID: %d zakończony\n",getpid());
			break;
		default:
			int wynik = 0;
			wait(NULL);	
			for(i=0; i<g; i++){
				wynik += i;
			}
			printf("Wynik (PID: %d) to %d \n", getpid(), wynik);	
			break;
	}

	return 0;
}
