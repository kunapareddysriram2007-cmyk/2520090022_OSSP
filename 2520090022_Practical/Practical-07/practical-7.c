#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globalVar = 100;
static int staticVar = 200;

void display()
{
    printf("Function Address (Code Segment) : %p\n", display);
}

int main()
{
    int stackVar = 300;
    int *heapVar;

    heapVar = (int *)malloc(sizeof(int));
    *heapVar = 400;

    display();

    printf("Global Variable Address : %p\n", &globalVar);
    printf("Static Variable Address : %p\n", &staticVar);
    printf("Heap Variable Address   : %p\n", heapVar);
    printf("Stack Variable Address  : %p\n", &stackVar);

    printf("\nProcess ID : %d\n", getpid());

    printf("\nPress Enter to exit...");
    getchar();

    free(heapVar);

    return 0;
}
