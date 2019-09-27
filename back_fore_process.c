#include "headers.h"

void handler(int sig)
{
    universal = 1;
    int pid;
    int status;
    int size = 100000;
    char *exit = (char *)malloc(size);
    char *exit_status = (char *)malloc(size);
    pid = waitpid(0,&status,WNOHANG);
    sprintf(exit,"\npid %d exited.\n",pid);
    if(WIFEXITED(status))
    {
        int ret = WEXITSTATUS(status);
        if(ret == 0)
        {
            sprintf(exit_status,"normally\n");
        }
        else
        {
            sprintf(exit_status,"abnormally\n");
        }
        //delete process
        int killed_jobid;
        for(int i = 1;i<iterator;i++)
        {
            //printf("JOB NMAE = %s\n", job_array[i].process_name);
            if(pid == job_array[i].process_id)
            {
                killed_jobid = i;
                for(int i = killed_jobid; i < iterator - 1; i++)
                {
        //    printf("dfghjk\n");
                job_array[i].process_id = job_array[i+1].process_id;
                strcpy(job_array[i].process_name,job_array[i+1].process_name);
                }
                //printf("came here\n");
                iterator -- ;
                break;
            }
        }

        //printf("%d\n",iterator);
        // DELETE PROCESS
    }
    if(pid >=1 )
    {
        write(2,exit,strlen(exit));
        write(2,exit_status,strlen(exit_status));
    }

    //signal(SIGCHLD,handler);
    free(exit);
}


void back_fore_process(char *process[], int length)
{
    int background = 0;
    
    for(int i =0; i < length; i++)
    {
        if(strcmp(process[i],"&") == 0)
        {
            background = 1;
            process[i] = NULL;
            break;
        }
    }
    //printf("IS BACKGROUND ? %d\n",background);
    int pid = fork();
    if(background==1)
        setpgid(0,0);
    childpid = pid;
    current_fore_id = childpid;

    if(pid == -1)
    {
        perror("fork");
    }
    if(pid == 0)
    {
        if(execvp(process[0],process) < 0)
        {
            perror("exec");
        }
        exit (0);
    }

    if(pid > 0)
    {
        if(background == 1)
        {
           // printf("ihht %d\n",iterator);
           // printf("ghjklgvhbj\n");
            job_array[iterator].process_id = pid;
            strcpy(job_array[iterator].process_name,process[0]);
           // printf("%s\n",job_array[iterator].process_name);
            iterator ++;
           // printf("it %d\n",iterator);
        }
        else
        {
            for(int c = 0;c<length;c++)
            {
                strcat(current_fore_process,process[c]);
                strcat(current_fore_process," ");
            }
        }
        if(background == 0)
        {
           // wait(NULL);
             int status;
             waitpid(-1, &status, WUNTRACED);
        }
    }
}
