#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(fd < 0)
    {
        printf("File opening failed.\n");
        return 1;
    }

    dup2(fd, STDOUT_FILENO);

    printf("This line is redirected to output.txt\n");
    printf("Linux I/O Redirection using dup2().\n");

    close(fd);

    return 0;
}
