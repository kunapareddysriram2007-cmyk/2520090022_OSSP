#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;

    // malloc()
    int *a = malloc(5 * sizeof(int));

    if (a == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    for (i = 0; i < 5; i++) {
        a[i] = (i + 1) * 10;
    }

    printf("malloc memory: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // calloc()
    int *b = calloc(5, sizeof(int));

    if (b == NULL) {
        printf("calloc failed\n");
        free(a);
        return 1;
    }

    printf("calloc memory: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    // realloc()
    int *temp = realloc(a, 10 * sizeof(int));

    if (temp == NULL) {
        printf("realloc failed\n");
        free(a);
        free(b);
        return 1;
    }

    a = temp;

    for (i = 5; i < 10; i++) {
        a[i] = (i + 1) * 10;
    }

    printf("After realloc: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // free()
    free(a);
    free(b);

    printf("Memory released successfully.\n");

    return 0;
}
