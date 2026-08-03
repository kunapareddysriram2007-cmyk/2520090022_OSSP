#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;

    int *arr1 = (int *)malloc(5 * sizeof(int));

    printf("Memory allocated using malloc:\n");
    for(i = 0; i < 5; i++)
    {
        arr1[i] = i + 1;
        printf("%d ", arr1[i]);
    }

    printf("\n");

    int *arr2 = (int *)calloc(5, sizeof(int));

    printf("Memory allocated using calloc:\n");
    for(i = 0; i < 5; i++)
    {
        printf("%d ", arr2[i]);
    }

    printf("\n");

    arr1 = (int *)realloc(arr1, 10 * sizeof(int));

    printf("Memory reallocated using realloc.\n");

    free(arr1);
    free(arr2);

    printf("Memory freed successfully.\n");

    return 0;
}
