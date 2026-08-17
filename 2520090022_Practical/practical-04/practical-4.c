#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t child1, child2, child3;
    int status;

    // Create first child
    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);
        printf("Child 1 completed.\n");
        exit(10);
    }

    // Create second child
    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2: PID = %d\n", getpid());
        sleep(4);
        printf("Child 2 completed.\n");
        exit(20);
    }

    // Create third child
    child3 = fork();

    if (child3 == 0)
    {
        printf("Child 3: PID = %d\n", getpid());
        sleep(1);
        printf("Child 3 completed.\n");
        exit(30);
    }

    // Parent process
    printf("Parent: PID = %d\n", getpid());

    // wait() waits for any one child
    pid_t finished = wait(&status);

    printf("wait(): Child with PID %d completed.\n", finished);

    if (WIFEXITED(status))
        printf("Exit status = %d\n", WEXITSTATUS(status));

    // waitpid() waits for a specific child
    waitpid(child2, &status, 0);

    printf("waitpid(): Child 2 with PID %d completed.\n", child2);

    if (WIFEXITED(status))
        printf("Exit status = %d\n", WEXITSTATUS(status));

    // Wait for remaining child
    waitpid(child1, &status, 0);
    printf("waitpid(): Child 1 completed.\n");

    return 0;
}
