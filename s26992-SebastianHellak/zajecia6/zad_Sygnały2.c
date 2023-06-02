#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


#define Lock "/tmp/lock"

void Signal1(int sig) {
    printf("Wykryto próbę uruchomienia drugiej instancji programu.\n");
}

void Signal2(int sig) {
    remove(Lock);
    exit(0);
}

int main() {
    FILE* fd, * File_lock;
    int masterPID = getpid();
    int filePID;
    char pojemnik[16];
    signal(SIGINT, Signal2);
    signal(SIGUSR1, Signal1);

    File_lock = fopen("File_lock", "r");
    if (File_lock) {
        fclose(File_lock);
        return 0;
    }

    File_lock = fopen("lock_file", "w");

    if (!File_lock) {
        fclose(File_lock);
        return 1;
    }

    if (access(Lock, F_OK) == 0) {
        fd = fopen(Lock, "r");

        while (fgets(pojemnik, 16, fd) != NULL) {
            filePID = atoi(pojemnik);
        }
        kill(filePID, SIGUSR1);
    }
    else {

        fd = fopen(Lock, "w");
        fprintf(fd, "%d", masterPID);
        fclose(fd);
        while (1) {
            sleep(1);
        }

    }

    fclose(File_lock);

    return 0;
}
