```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // First child - executes ls -l
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {

        // Close unused read end
        close(fd[0]);

        // Redirect stdout to pipe
        dup2(fd[1], STDOUT_FILENO);

        // Close original descriptor
        close(fd[1]);

        // Execute ls -l
        execlp("ls", "ls", "-l", (char *)NULL);

        // Only reached if exec fails
        perror("exec ls");
        exit(1);
    }

    // Second child - executes grep ".c"
    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {

        // Close unused write end
        close(fd[1]);

        // Redirect stdin from pipe
        dup2(fd[0], STDIN_FILENO);

        // Close original descriptor
        close(fd[0]);

        // Execute grep ".c"
        execlp("grep", "grep", ".c", (char *)NULL);

        // Only reached if exec fails
        perror("exec grep");
        exit(1);
    }

    // Parent doesn't use the pipe
    close(fd[0]);
    close(fd[1]);

    // Wait for both children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Pipeline execution completed.\n");

    return 0;
}
```

