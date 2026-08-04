#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_JOBS 10

typedef struct
{
    int id;
    pid_t pid;
    char command[100];
    int active;
} Job;

Job jobs[MAX_JOBS];
int jobCount = 0;

void updateJobs()
{
    int status;

    for(int i = 0; i < jobCount; i++)
    {
        if(jobs[i].active)
        {
            if(waitpid(jobs[i].pid, &status, WNOHANG) > 0)
            {
                printf("\nJob [%d] Completed\n", jobs[i].id);
                jobs[i].active = 0;
            }
        }
    }
}

void listJobs()
{
    printf("\nActive Jobs\n");

    for(int i = 0; i < jobCount; i++)
    {
        if(jobs[i].active)
        {
            printf("[%d] PID=%d STATUS=Running CMD=%s\n",
                   jobs[i].id,
                   jobs[i].pid,
                   jobs[i].command);
        }
    }

    printf("\n");
}

int main()
{
    char input[100];

    while(1)
    {
        updateJobs();

        printf("MyShell> ");

        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")]='\0';

        if(strcmp(input,"exit")==0)
            break;

        if(strcmp(input,"jobs")==0)
        {
            listJobs();
            continue;
        }

        if(strncmp(input,"run ",4)==0)
        {
            char *cmd=input+4;

            pid_t pid=fork();

            if(pid==0)
            {
                execlp(cmd,cmd,NULL);
                perror("exec");
                exit(1);
            }

            jobs[jobCount].id=jobCount+1;
            jobs[jobCount].pid=pid;
            strcpy(jobs[jobCount].command,cmd);
            jobs[jobCount].active=1;

            printf("Started Job [%d] PID=%d\n",
                   jobs[jobCount].id,pid);

            jobCount++;

            continue;
        }

        if(strncmp(input,"fg ",3)==0)
        {
            int id=atoi(input+3);

            for(int i=0;i<jobCount;i++)
            {
                if(jobs[i].id==id && jobs[i].active)
                {
                    printf("Bringing Job [%d] to Foreground...\n",id);

                    waitpid(jobs[i].pid,NULL,0);

                    jobs[i].active=0;

                    printf("Foreground Job Finished.\n");
                    break;
                }
            }

            continue;
        }

        printf("\nCommands:\n");
        printf("run <program>\n");
        printf("jobs\n");
        printf("fg <job-id>\n");
        printf("exit\n\n");
    }

    return 0;
}
