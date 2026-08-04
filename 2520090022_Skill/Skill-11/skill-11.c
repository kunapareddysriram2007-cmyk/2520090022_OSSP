#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 10
#define MAX_LEN 100

int main()
{
    char history[MAX_HISTORY][MAX_LEN];
    char input[MAX_LEN];
    int count = 0, i;

    while (1)
    {
        printf("MyShell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
            break;

        if (strcmp(input, "history") == 0)
        {
            printf("\nCommand History:\n");

            for (i = 0; i < count; i++)
                printf("%d. %s\n", i + 1, history[i]);

            printf("\n");
            continue;
        }

        if (count < MAX_HISTORY)
        {
            strcpy(history[count], input);
            count++;
        }
        else
        {
            for (i = 1; i < MAX_HISTORY; i++)
                strcpy(history[i - 1], history[i]);

            strcpy(history[MAX_HISTORY - 1], input);
        }

        if (strchr(input, '|'))
        {
            char temp[MAX_LEN];
            strcpy(temp, input);

            char *token = strtok(temp, "|");

            printf("\nPipeline Commands:\n");

            while (token != NULL)
            {
                while (*token == ' ')
                    token++;

                printf("%s\n", token);

                token = strtok(NULL, "|");
            }

            printf("Pipeline Layout Valid\n\n");
        }
        else
        {
            printf("Command Stored.\n");
        }
    }

    return 0;
}
