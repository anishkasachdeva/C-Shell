#include "headers.h"

void fg_func(char *command_name[],int length)
{
    int jobid,status;
    sscanf(command_name[1],"%d",&jobid);
    if(jobid>=iterator)
    {
        printf("Such a background process doesn't exist\n");
    }
    else
    {
        int pid = job_array[jobid].process_id;
        kill(pid,SIGCONT);
        waitpid(pid,&status,WUNTRACED);
        for(int i = jobid;i<iterator-1;i++)
        {
        //    printf("drfgh\n");
            job_array[i].process_id = job_array[i+1].process_id;
            strcpy(job_array[i].process_name,job_array[i+1].process_name);
        }
        iterator --;
    }
}