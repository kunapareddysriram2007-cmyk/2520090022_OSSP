#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: PID = %d\n", getpid());
        printf("Child exiting...\n");
        exit(0);
    }
    else
    {
        printf("Parent: PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        // Parent waits for child
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("Child terminated normally.\n");
            printf("Exit status: %d\n", WEXITSTATUS(status));
        }

        printf("Parent exiting...\n");
    }

    return 0;
}
