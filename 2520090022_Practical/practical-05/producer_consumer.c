```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define COUNT 100000

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child - Consumer
        close(fd[1]);

        int value;
        long count = 0;
        long sum = 0;

        while (read(fd[0], &value, sizeof(value)) > 0) {
            sum += value;
            count++;
        }

        close(fd[0]);

        printf("Consumer received %ld values\n", count);
        printf("Sum = %ld\n", sum);

        exit(0);
    }

    else {
        // Parent - Producer
        close(fd[0]);

        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 1; i <= COUNT; i++) {
            if (write(fd[1], &i, sizeof(i)) == -1) {
                perror("write");
                break;
            }
        }

        close(fd[1]);

        waitpid(pid, NULL, 0);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("Producer sent %d values\n", COUNT);
        printf("Communication time = %.6f seconds\n", time);

        if (time > 0) {
            double rate =
                (COUNT * sizeof(int)) / time;

            printf("Communication rate = %.2f bytes/sec\n",
                   rate);
        }
    }

    return 0;
}
```

