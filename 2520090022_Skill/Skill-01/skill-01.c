#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed\n");
        return 1;
    }

    if(pid == 0)
    {
        printf("\n----- Child Process -----\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("\nExecuting 'ls -l' using exec()\n");

        execl("/bin/ls", "ls", "-l", NULL);

        perror("exec failed");
    }
    else
    {
        printf("\n----- Parent Process -----\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        wait(NULL);

        printf("\nChild process completed.\n");
    }

    return 0;
}
