#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_JOBS 10

typedef struct
{
    pid_t pid;
    char command[100];
    int active;
} Job;

Job jobs[MAX_JOBS];

void showJobs()
{
    int i;

    printf("\nBackground Jobs\n");

    for(i = 0; i < MAX_JOBS; i++)
    {
        if(jobs[i].active)
        {
            printf("[%d] PID=%d Command=%s\n",
                   i + 1,
                   jobs[i].pid,
                   jobs[i].command);
        }
    }

    printf("\n");
}

void updateJobs()
{
    int i;
    int status;

    for(i = 0; i < MAX_JOBS; i++)
    {
        if(jobs[i].active)
        {
            if(waitpid(jobs[i].pid, &status, WNOHANG) > 0)
            {
                printf("Job Completed: %s\n", jobs[i].command);
                jobs[i].active = 0;
            }
        }
    }
}

int main()
{
    char input[100];

    while(1)
    {
        updateJobs();

        printf("MyShell> ");

        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, "exit") == 0)
            break;

        if(strcmp(input, "jobs") == 0)
        {
            showJobs();
            continue;
        }

        if(strncmp(input, "run ", 4) == 0)
        {
            char *command = input + 4;

            pid_t pid = fork();

            if(pid == 0)
            {
                execlp(command, command, NULL);
                perror("exec");
                exit(1);
            }
            else
            {
                int i;

                for(i = 0; i < MAX_JOBS; i++)
                {
                    if(!jobs[i].active)
                    {
                        jobs[i].pid = pid;
                        strcpy(jobs[i].command, command);
                        jobs[i].active = 1;
                        break;
                    }
                }

                printf("Started Background Job PID=%d\n", pid);
            }

            continue;
        }

        printf("Commands:\n");
        printf("run <command>\n");
        printf("jobs\n");
        printf("exit\n");
    }

    return 0;
}
