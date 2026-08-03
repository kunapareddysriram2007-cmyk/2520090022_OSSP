#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
    int fd;
    char *map;

    fd = open("sample.txt", O_RDWR);

    if(fd < 0)
    {
        perror("open");
        return 1;
    }

    map = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(map == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("File Contents:\n%s\n", map);

    strcpy(map, "Memory Mapped I/O Successful\n");

    munmap(map, 4096);

    close(fd);

    return 0;
}
