#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_JOBS 10

typedef struct
{
    int id;
    pid_t pid;
    int stopped;
} Job;

Job jobs[MAX_JOBS];
int count = 0;

void showJobs()
{
    printf("\nJob Table\n");

    for(int i = 0; i < count; i++)
    {
        printf("[%d] PID=%d  %s\n",
               jobs[i].id,
               jobs[i].pid,
               jobs[i].stopped ? "Stopped" : "Running");
    }

    printf("\n");
}

int main()
{
    char input[100];

    while(1)
    {
        printf("MyShell> ");

        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")] = '\0';

        if(strcmp(input,"exit")==0)
            break;

        if(strcmp(input,"jobs")==0)
        {
            showJobs();
            continue;
        }

        if(strcmp(input,"run")==0)
        {
            pid_t pid = fork();

            if(pid==0)
            {
                while(1)
                    sleep(1);
            }

            jobs[count].id = count + 1;
            jobs[count].pid = pid;
            jobs[count].stopped = 0;

            printf("Started Job [%d] PID=%d\n",
                    jobs[count].id,pid);

            count++;
            continue;
        }

        if(strncmp(input,"stop ",5)==0)
        {
            int id = atoi(input+5);

            for(int i=0;i<count;i++)
            {
                if(jobs[i].id==id)
                {
                    kill(jobs[i].pid,SIGSTOP);
                    jobs[i].stopped=1;
                    printf("Job %d Stopped\n",id);
                }
            }

            continue;
        }

        if(strncmp(input,"bg ",3)==0)
        {
            int id=atoi(input+3);

            for(int i=0;i<count;i++)
            {
                if(jobs[i].id==id)
                {
                    kill(jobs[i].pid,SIGCONT);
                    jobs[i].stopped=0;
                    printf("Job %d Resumed\n",id);
                }
            }

            continue;
        }

        printf("\nCommands:\n");
        printf("run\n");
        printf("stop <job-id>\n");
        printf("bg <job-id>\n");
        printf("jobs\n");
        printf("exit\n\n");
    }

    for(int i=0;i<count;i++)
    {
        kill(jobs[i].pid,SIGKILL);
        waitpid(jobs[i].pid,NULL,0);
    }

    return 0;
}
