#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define REQUEST_FIFO "request_fifo"
#define RESPONSE_FIFO "response_fifo"
#define SIZE 256

int main() {
    char buffer[SIZE];

    mkfifo(REQUEST_FIFO, 0666);
    mkfifo(RESPONSE_FIFO, 0666);

    printf("Server started. Waiting for client...\n");

    while (1) {
        int request_fd = open(REQUEST_FIFO, O_RDONLY);

        if (request_fd == -1) {
            perror("open request_fifo");
            exit(1);
        }

        int n = read(request_fd, buffer, SIZE - 1);
        close(request_fd);

        if (n > 0) {
            buffer[n] = '\0';

            printf("Client message: %s\n", buffer);

            if (strcmp(buffer, "exit") == 0) {
                int response_fd = open(RESPONSE_FIFO, O_WRONLY);
                write(response_fd, "Server shutting down", 20);
                close(response_fd);
                break;
            }

            char response[SIZE];
            snprintf(response, SIZE, "Server processed: %s", buffer);

            int response_fd = open(RESPONSE_FIFO, O_WRONLY);

            if (response_fd == -1) {
                perror("open response_fifo");
                exit(1);
            }

            write(response_fd, response, strlen(response) + 1);
            close(response_fd);
        }
    }

    unlink(REQUEST_FIFO);
    unlink(RESPONSE_FIFO);

    return 0;
}
