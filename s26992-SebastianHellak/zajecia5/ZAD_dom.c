#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const* argv[])
{
    int STAT, i;
    unsigned int P_ID;

    for (i = 0; i < 2; i++)
    {
        P_ID = fork();
        if (P_ID == 0)
            break;
    }
    if (P_ID == 0)
    {
        for (i = 0; i < 2; i++)
        {
            if (fork() == 0)
                break;
        }
    }
    while (wait(&STAT) < 0);

    return 0;
}
