#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signalHandler(int sig)
{
    printf("\nSIGINT Captured\n");
}

int main()
{
    signal(SIGINT, signalHandler);

    int pipefd[2];

    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid1 = fork();

    if(pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp("ls","ls","-l",NULL);

        perror("exec");
        exit(1);
    }

    pid_t pid2 = fork();

    if(pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp("grep","grep",".c",NULL);

        perror("exec");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    printf("\nPipeline Demonstrated Successfully\n");
    printf("Press Ctrl+C to test signal handling.\n");

    pause();

    return 0;
}
