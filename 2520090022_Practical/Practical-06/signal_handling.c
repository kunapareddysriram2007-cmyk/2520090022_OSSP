#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    if(sig == SIGINT)
        printf("\nSIGINT received.\n");

    else if(sig == SIGTERM)
        printf("\nSIGTERM received.\n");

    else if(sig == SIGUSR1)
        printf("\nSIGUSR1 received.\n");
}

int main()
{
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    signal(SIGUSR1, handler);

    printf("Process ID: %d\n", getpid());

    while(1)
    {
        printf("Waiting for signals...\n");
        sleep(5);
    }

    return 0;
}
