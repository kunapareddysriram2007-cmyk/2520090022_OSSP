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

        else if(strcmp(command, "append") == 0)
        {
            int fd = open("append.txt",
                          O_WRONLY | O_CREAT | O_APPEND,
                          0644);

            if(fd < 0)
            {
                perror("append");
                continue;
            }

            int save = dup(STDOUT_FILENO);

            dup2(fd, STDOUT_FILENO);

            printf("New line appended successfully.");

            fflush(stdout);

            dup2(save, STDOUT_FILENO);

            close(save);
            close(fd);

            printf("Data appended to append.txt\n");
        }

        else if(strcmp(command, "stderr") == 0)
        {
            int fd = open("error.txt",
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

            if(fd < 0)
            {
                perror("error");
                continue;
            }

            int save = dup(STDERR_FILENO);

            dup2(fd, STDERR_FILENO);

            fprintf(stderr,
                    "Sample Error: File not found.\n");

            fflush(stderr);

            dup2(save, STDERR_FILENO);

            close(save);
            close(fd);

            printf("Error redirected to error.txt\n");
        }

        else
        {
            printf("Commands:\n");
            printf("append\n");
            printf("stderr\n");
            printf("exit\n");
        }
    }

    return 0;
}
