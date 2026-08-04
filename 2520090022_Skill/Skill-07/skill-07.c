#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char command[100];
    char *path;
    char *dir;

    while(1)
    {
        printf("MyShell> ");

        if(fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\n")] = '\0';

        if(strcmp(command, "exit") == 0)
            break;

        path = getenv("PATH");

        if(path == NULL)
        {
            printf("PATH variable not found.\n");
            return 1;
        }

        printf("\nPATH Directories:\n");

        char temp[1000];
        strcpy(temp, path);

        dir = strtok(temp, ":");

        while(dir != NULL)
        {
            printf("%s\n", dir);
            dir = strtok(NULL, ":");
        }

        pid_t pid = fork();

        if(pid == 0)
        {
            printf("\nExecuting Command...\n");

            execlp(command, command, NULL);

            perror("Command Not Found");
            exit(1);
        }
        else if(pid > 0)
        {
            waitpid(pid, NULL, 0);

            printf("Child Process Finished.\n");
        }
        else
        {
            perror("Fork Failed");
        }

        printf("----------------------------------\n");
    }

    return 0;
}
