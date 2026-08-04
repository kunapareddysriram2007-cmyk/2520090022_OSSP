#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char input[200];
    char cwd[1024];

    while(1)
    {
        getcwd(cwd, sizeof(cwd));
        printf("MyShell:%s$ ", cwd);

        if(fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, "pwd") == 0)
        {
            printf("%s\n", cwd);
            continue;
        }

        if(strcmp(input, "exit") == 0)
        {
            printf("Cleaning up resources...\n");
            printf("Exiting Shell.\n");
            break;
        }

        if(strncmp(input, "export ", 7) == 0)
        {
            char *var = input + 7;
            char *equal = strchr(var, '=');

            if(equal == NULL)
            {
                printf("Invalid export syntax.\n");
                continue;
            }

            *equal = '\0';
            char *name = var;
            char *value = equal + 1;

            if(strlen(name) == 0)
            {
                printf("Invalid variable name.\n");
                continue;
            }

            if(setenv(name, value, 1) == 0)
            {
                printf("%s=%s exported successfully.\n", name, value);
            }
            else
            {
                perror("export");
            }

            continue;
        }

        if(input[0] == '$')
        {
            char *value = getenv(input + 1);

            if(value)
                printf("%s\n", value);
            else
                printf("Variable not found.\n");

            continue;
        }

        printf("Unknown Command\n");
    }

    return 0;
}
