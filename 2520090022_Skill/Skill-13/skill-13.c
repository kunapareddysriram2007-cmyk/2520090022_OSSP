#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char command[100];

    while(1)
    {
        printf("MyShell> ");

        if(fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\n")] = '\0';

        if(strcmp(command, "exit") == 0)
            break;

        if(strcmp(command, "input") == 0)
        {
            int fd = open("input.txt", O_RDONLY);

            if(fd < 0)
            {
                perror("Input File");
                continue;
            }

            dup2(fd, STDIN_FILENO);
            close(fd);

            char line[100];

            printf("\nReading from input.txt\n\n");

            while(fgets(line, sizeof(line), stdin))
                printf("%s", line);

            freopen("/dev/tty", "r", stdin);

            printf("\nInput Restored\n\n");
        }

        else if(strcmp(command, "output") == 0)
        {
            int fd = open("output.txt",
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

            if(fd < 0)
            {
                perror("Output File");
                continue;
            }

            dup2(fd, STDOUT_FILENO);

            printf("This line is written into output.txt\n");

            fflush(stdout);

            close(fd);

            freopen("/dev/tty", "w", stdout);

            printf("Output Restored\n");
        }

        else
        {
            printf("Commands:\n");
            printf("input\n");
            printf("output\n");
            printf("exit\n");
        }
    }

    return 0;
}
