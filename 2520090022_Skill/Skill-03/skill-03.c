#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 10

int main()
{
    char **history;
    char *command;
    int count = 0;
    int i;

    history = (char **)malloc(MAX_HISTORY * sizeof(char *));
    command = (char *)malloc(100);

    if(history == NULL || command == NULL)
    {
        printf("Memory Allocation Failed\n");
        return 1;
    }

    while(1)
    {
        printf("MyShell> ");

        fgets(command, 100, stdin);

        command[strcspn(command, "\n")] = '\0';

        if(strcmp(command, "exit") == 0)
            break;

        if(strcmp(command, "history") == 0)
        {
            printf("\nCommand History:\n");

            for(i = 0; i < count; i++)
                printf("%d. %s\n", i + 1, history[i]);

            continue;
        }

        history[count] = (char *)malloc(strlen(command) + 1);
        strcpy(history[count], command);

        count++;

        if(count >= MAX_HISTORY)
        {
            printf("History Buffer Full\n");
            break;
        }

        printf("Command Executed: %s\n", command);
    }

    for(i = 0; i < count; i++)
        free(history[i]);

    free(history);
    free(command);

    return 0;
}
