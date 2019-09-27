#include "headers.h"

void bg_func(char *command_name[],int length)
{
    int jobid;
    int existence = 0;
    for(int i=1;i<iterator;i++)
    {
        sscanf(command_name[1],"%d",&jobid);
        if(i == jobid)
        {
            existence = 1;
            kill(job_array[i].process_id, SIGTTIN);
            kill(job_array[i].process_id, SIGCONT);
            break;
        }
    }
    if(existence == 0)
    {
        printf("Such a job doesn't exist!\n");
    }
}