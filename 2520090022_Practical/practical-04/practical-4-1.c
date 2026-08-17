#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

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

        // Parent does not call wait()
        // Child becomes zombie after exiting
        sleep(30);

        printf("Parent exiting...\n");
    }

    return 0;
}
