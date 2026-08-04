#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void executeCommand(char input[])
{
    char *args[10];
    int i = 0;

    args[i] = strtok(input, " ");

    while(args[i] != NULL && i < 9)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }

    if(args[0] == NULL)
    {
        printf("Error: Empty Command\n");
        return;
    }

    pid_t pid = fork();

    if(pid == 0)
    {
        execvp(args[0], args);

        perror("Execution Failed");
        exit(1);
    }

    wait(NULL);
}

int main()
{
    char input[100];

    while(1)
    {
        printf("MyShell> ");

        if(fgets(input,sizeof(input),stdin)==NULL)
            break;

        input[strcspn(input,"\n")] = '\0';

        if(strlen(input)==0)
        {
            printf("Empty Input\n");
            continue;
        }

        if(strcmp(input,"exit")==0)
            break;

        executeCommand(input);
    }

    printf("Shell Closed Successfully\n");

    return 0;
}
