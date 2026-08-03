#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    char command[100];

    printf("Enter Linux command: ");
    scanf("%99s", command);

    pid = fork();

    if (pid < 0)
    {
        printf("Failed to create child process.\n");
        return 1;
    }
    else if (pid == 0)
    {
        // Child Process
        printf("\n--- Child Process ---\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("Executing command: %s\n\n", command);

        execlp(command, command, NULL);

        // Executes only if exec() fails
        perror("Command execution failed");
        exit(1);
    }
    else
    {
        // Parent Process
        printf("\n--- Parent Process ---\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        // Wait for child to finish
        wait(NULL);

        printf("\nChild process has finished execution.\n");
    }

    return 0;
}
