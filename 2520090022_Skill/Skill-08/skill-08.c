#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execute_builtin(char *cmd)
{
    if(strcmp(cmd, "pwd") == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("Current Directory: %s\n", cwd);
    }
    else if(strcmp(cmd, "help") == 0)
    {
        printf("Built-in Commands:\n");
        printf("pwd\n");
        printf("help\n");
        printf("exit\n");
    }
    else
    {
        printf("Invalid Built-in Command\n");
    }
}

int main()
{
    char input[100];

    while(1)
    {
        printf("MyShell> ");

        if(fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, "exit") == 0)
        {
            printf("Exiting Shell...\n");
            break;
        }

        if(input[0] == '$')
        {
            char *value = getenv(input + 1);

            if(value != NULL)
                printf("Expanded Value: %s\n", value);
            else
                printf("Undefined Variable\n");

            continue;
        }

        if(strcmp(input, "pwd") == 0 ||
           strcmp(input, "help") == 0)
        {
            execute_builtin(input);
        }
        else
        {
            printf("Command not found.\n");
        }

        printf("----------------------------\n");
    }

    return 0;
}
