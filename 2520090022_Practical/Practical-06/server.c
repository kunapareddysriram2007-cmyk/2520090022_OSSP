#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main()
{
    char message[100];

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    int fd1 = open(FIFO1, O_RDONLY);
    int fd2 = open(FIFO2, O_WRONLY);

    read(fd1, message, sizeof(message));

    printf("Message from Client: %s\n", message);

    strcat(message, " [Processed by Server]");

    write(fd2, message, strlen(message) + 1);

    close(fd1);
    close(fd2);

    return 0;
}
