#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

        printf("\nInput : %s\n", command);

        if(strchr(command, '\\'))
        {
            printf("Escape Sequence Detected\n");
            printf("Escaped characters preserved.\n");
        }

        pid_t pid = fork();

        if(pid < 0)
        {
            printf("Fork Failed\n");
            continue;
        }

        if(pid == 0)
        {
            printf("\nChild Process Executing...\n");

            execl("/bin/sh", "sh", "-c", command, NULL);

            perror("Execution Failed");
            exit(1);
        }
        else
        {
            wait(NULL);

            printf("\nParent Process: Child Finished\n");
        }

        printf("--------------------------------\n");
    }

    return 0;
}
