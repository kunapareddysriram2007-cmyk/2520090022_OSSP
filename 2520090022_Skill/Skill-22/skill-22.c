#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *buffer;

    buffer = (char *)malloc(100);

    if(buffer == NULL)
    {
        printf("Memory Allocation Failed\n");
        return 1;
    }

    strcpy(buffer, "Operating Systems Skill-22");

    printf("Message : %s\n", buffer);

    free(buffer);

    buffer = NULL;

    printf("Memory Released Successfully\n");

    return 0;
}
