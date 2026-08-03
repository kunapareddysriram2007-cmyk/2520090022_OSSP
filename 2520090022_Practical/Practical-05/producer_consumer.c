#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buffer[100];

    if(pipe(fd) == -1)
    {
        printf("Pipe creation failed.\n");
        return 1;
    }

    pid = fork();

    if(pid < 0)
    {
        printf("Fork failed.\n");
        return 1;
    }

    if(pid > 0)
    {
        close(fd[0]);

        strcpy(buffer, "Hello from Parent (Producer)");

        write(fd[1], buffer, strlen(buffer) + 1);

        printf("Producer sent: %s\n", buffer);

        close(fd[1]);

        wait(NULL);
    }
    else
    {
        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        printf("Consumer received: %s\n", buffer);

        close(fd[0]);
    }

    return 0;
}
