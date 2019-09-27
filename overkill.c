#include "headers.h"

void overkill_func()
{
    for(int i=1;i<iterator;i++)
    {
        kill(job_array[i].process_id,9);
      //  job_array[i].process_id = 0;
        //strcpy(job_array[i].process_name,'\0');
        //job_array[i].process_name = '\0';
    }
    iterator = 1;
    //struct jobs job_array[10000];   
}