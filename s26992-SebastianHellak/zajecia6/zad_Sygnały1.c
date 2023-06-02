#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void signal_Handler(int sig) {
    if (sig == SIGUSR1) {
        printf("Otrzymano sygnal: %d\n", sig);
        exit(1);
    }
}

int main() {
    int PID = getpid();

    printf("Pid to %d\n", PID);
    while (1) {
        signal(SIGUSR1, signalHandler);
    }

    return 0;
}
