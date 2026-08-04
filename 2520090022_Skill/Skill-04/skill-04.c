#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 20

int main()
{
    char input[100];
    char *token;
    char *tokens[MAX_TOKENS];
    int count = 0;
    int i;

    while(1)
    {
        printf("MyShell> ");

        if(fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if(strlen(input) == 0)
        {
            printf("Empty Command!\n");
            continue;
        }

        if(strcmp(input, "exit") == 0)
            break;

        count = 0;

        token = strtok(input, " \t");

        while(token != NULL && count < MAX_TOKENS)
        {
            tokens[count++] = token;
            token = strtok(NULL, " \t");
        }

        printf("\nTokens:\n");

        for(i = 0; i < count; i++)
            printf("Token %d : %s\n", i + 1, tokens[i]);

        printf("\nParse Structure:\n");

        if(count > 0)
        {
            printf("Command : %s\n", tokens[0]);

            if(count > 1)
            {
                printf("Arguments:\n");

                for(i = 1; i < count; i++)
                    printf("  %s\n", tokens[i]);
            }
        }

        printf("------------------------\n");
    }

    return 0;
}
