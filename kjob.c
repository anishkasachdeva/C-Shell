#include "headers.h"

void kjob_func(char *command_process[])
{
    int killed_jobid,signal_num;
    sscanf(command_process[1], "%d", &killed_jobid); //to convert string into integer
    sscanf(command_process[2],"%d",&signal_num);
    for(int i=1;i<iterator;i++)
    {
        if(killed_jobid == i)
        {
            //printf("Killinfg %s\n", job_array[i].process_name);
            kill(job_array[i].process_id,signal_num);
            break;
        }
    }
    //printf("ite %d\n",iterator);
    // for(int i = killed_jobid;i<iterator-1;i++)
    // {
    //     job_array[i].process_id = job_array[i+1].process_id;
    //     strcpy(job_array[i].process_name,job_array[i+1].process_name);
    // }
    //job_array[iterator - 1].process_id = 0;
    //strcpy(job_array[iterator - 1].process_name, "");
    // iterator --;

    // for(int i =1 ; i< iterator; i++)
    // {
    //     printf("%d %s \n",job_array[i].process_id,job_array[i].process_name);
    // }
    // printf("** i =%d\n", iterator);
    //printf("iteuuuu %d\n",iterator);
}
