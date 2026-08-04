#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int fd;
    int pipefd[2];

    printf("----- Combined Redirection -----\n");

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(fd < 0)
    {
        perror("open");
        return 1;
    }

    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    printf("Standard Output redirected.\n");
    fprintf(stderr, "Standard Error redirected.\n");

    close(fd);

    fflush(stdout);
    fflush(stderr);

    freopen("/dev/tty", "w", stdout);
    freopen("/dev/tty", "w", stderr);

    printf("\nCombined redirection completed.\n");

    printf("\n----- Pipe + Redirection -----\n");

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
        fd = open("output.txt",
                  O_WRONLY | O_CREAT | O_APPEND,
                  0644);

        dup2(pipefd[0], STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);
        close(fd);

        execlp("grep","grep",".c",NULL);

        perror("exec");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    printf("Pipeline executed successfully.\n");

    return 0;
}
