#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid == 0)
    {
        printf("Child Process\n");
        printf("PID : %d\n", getpid());
        printf("Child exiting...\n");
        exit(0);
    }
    else
    {
        printf("Parent PID : %d\n", getpid());
        printf("Sleeping for 20 seconds...\n");

        sleep(20);

        printf("Parent exiting...\n");
    }

    return 0;
}
