#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char input[100];
    char current[1024];
    char previous[1024] = "";

    while(1)
    {
        getcwd(current, sizeof(current));
        printf("MyShell:%s$ ", current);

        if(fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, "exit") == 0)
            break;

        if(strcmp(input, "pwd") == 0)
        {
            printf("%s\n", current);
            continue;
        }

        if(strcmp(input, "help") == 0)
        {
            printf("\nBuilt-in Commands:\n");
            printf("cd <directory>\n");
            printf("cd -\n");
            printf("pwd\n");
            printf("help\n");
            printf("exit\n\n");
            continue;
        }

        if(strncmp(input, "cd", 2) == 0)
        {
            char *path = input + 2;

            while(*path == ' ')
                path++;

            if(strcmp(path, "-") == 0)
            {
                if(strlen(previous) == 0)
                {
                    printf("No previous directory.\n");
                }
                else
                {
                    char temp[1024];
                    strcpy(temp, current);

                    if(chdir(previous) == 0)
                    {
                        printf("%s\n", previous);
                        strcpy(previous, temp);
                    }
                    else
                    {
                        perror("cd");
                    }
                }
            }
            else
            {
                strcpy(previous, current);

                if(chdir(path) != 0)
                {
                    perror("cd");
                }
            }

            continue;
        }

        printf("Invalid Command\n");
    }

    return 0;
}
