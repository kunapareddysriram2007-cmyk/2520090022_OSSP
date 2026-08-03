#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global = 100;

int main()
{
    pid_t pid;

    pid = fork();

    if(pid == 0)
    {
        printf("\nChild Process\n");
        printf("PID : %d\n", getpid());

        printf("Global Before : %d\n", global);

        global = 500;

        printf("Global After : %d\n", global);
    }
    else
    {
        wait(NULL);

        printf("\nParent Process\n");
        printf("PID : %d\n", getpid());

        printf("Global Value : %d\n", global);
    }

    return 0;
}
