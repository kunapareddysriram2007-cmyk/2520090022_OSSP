#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int source, destination;
    char buffer[1024];
    ssize_t bytesRead;

    source = open("input.txt", O_RDONLY);

    if(source < 0)
    {
        printf("Cannot open input file.\n");
        return 1;
    }

    destination = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(destination < 0)
    {
        printf("Cannot create output file.\n");
        close(source);
        return 1;
    }

    lseek(source, 0, SEEK_SET);

    while((bytesRead = read(source, buffer, sizeof(buffer))) > 0)
    {
        write(destination, buffer, bytesRead);
    }

    close(source);
    close(destination);

    printf("File copied successfully.\n");

    return 0;
}
