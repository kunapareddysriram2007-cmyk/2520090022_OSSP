#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main()
{
    char message[100];

    int fd1 = open(FIFO1, O_WRONLY);
    int fd2 = open(FIFO2, O_RDONLY);

    printf("Enter Message: ");
    fgets(message, sizeof(message), stdin);

    write(fd1, message, strlen(message) + 1);

    read(fd2, message, sizeof(message));

    printf("Server Response: %s\n", message);

    close(fd1);
    close(fd2);

    return 0;
}
