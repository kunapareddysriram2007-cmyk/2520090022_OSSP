#include <stdio.h>
#include <string.h>

int main()
{
    char input[200];

    while(1)
    {
        printf("MyShell> ");

        if(fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, "exit") == 0)
            break;

        if(strlen(input) == 0)
        {
            printf("Empty Command!\n");
            continue;
        }

        printf("\nOriginal Input : %s\n", input);

        if(strchr(input, '\''))
        {
            printf("Single Quotes Detected\n");
            printf("Literal Content Preserved\n");
            printf("Variable Expansion Ignored\n");
        }

        if(strchr(input, '\"'))
        {
            printf("Double Quotes Detected\n");
            printf("Spaces Preserved\n");
            printf("Variable Expansion Allowed\n");
        }

        printf("Command Accepted\n");
        printf("--------------------------\n");
    }

    return 0;
}
