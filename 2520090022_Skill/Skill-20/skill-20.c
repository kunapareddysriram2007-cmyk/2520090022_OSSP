#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t childPid = -1;
int stopped = 0;

void sigtstpHandler(int sig)
{
    printf("\nSIGTSTP (Ctrl+Z) Received\n");

    if(childPid > 0)
    {
        kill(childPid, SIGSTOP);
        stopped = 1;
        printf("Foreground Process Suspended\n");
    }
}

int main()
{
    signal(SIGTSTP, sigtstpHandler);

    while(1)
    {
        int choice;

        printf("\n1. Start Process\n");
        printf("2. Resume Process\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            childPid = fork();

            if(childPid == 0)
            {
                setpgid(0,0);

                printf("Child Process Running...\n");

                while(1)
                    sleep(1);
            }

            setpgid(childPid, childPid);

            waitpid(childPid, NULL, WUNTRACED);

            if(stopped)
                printf("Job Saved in Job Table\n");
        }

        else if(choice == 2)
        {
            if(stopped)
            {
                printf("Resuming Job...\n");

                kill(childPid, SIGCONT);

                stopped = 0;

                waitpid(childPid, NULL, WUNTRACED);
            }
            else
            {
                printf("No Suspended Job\n");
            }
        }

        else if(choice == 3)
        {
            if(childPid > 0)
            {
                kill(childPid, SIGKILL);
                waitpid(childPid, NULL, 0);
            }

            break;
        }
    }

    printf("Shell Closed\n");

    return 0;
}
