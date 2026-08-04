#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t foregroundPid = -1;

void sigintHandler(int sig)
{
    printf("\nSIGINT Received by Shell\n");

    if(foregroundPid > 0)
    {
        printf("Forwarding SIGINT to Child Process (%d)\n", foregroundPid);
        kill(foregroundPid, SIGINT);
    }
    else
    {
        printf("No Foreground Process Running\n");
    }
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigintHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    while(1)
    {
        printf("\n1. Run Foreground Job\n");
        printf("2. Exit\n");
        printf("Choice: ");

        int choice;
        scanf("%d", &choice);

        if(choice == 2)
            break;

        if(choice == 1)
        {
            foregroundPid = fork();

            if(foregroundPid == 0)
            {
                printf("Child Running... Press Ctrl+C\n");

                while(1)
                    sleep(1);
            }

            waitpid(foregroundPid, NULL, 0);

            printf("Foreground Job Finished\n");

            foregroundPid = -1;
        }
    }

    printf("Shell Exiting...\n");

    return 0;
}
