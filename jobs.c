#include "headers.h"


void jobs_func()
{
    //printf("%d\n",iterator);
    /*for(int i = 1; i<iterator;i++)
    {
        printf("%d ",job_array[i].process_id);
        printf("%s \n",job_array[i].process_name);
        
    }*/
    //printf("entered job with iterator %d\n", iterator);
    int jobid;
   // printf("i %d\n",iterator);
    for(int i=1;i<iterator;i++)
    {
        jobid = i;
        char filedata[10000],path[10000],*p;
        snprintf(path,sizeof(path), "/proc/%d/status" , job_array[i].process_id);
        FILE * filePointer;
        filePointer = fopen(path,"r");
        if(filePointer == NULL)
        {
            printf("Cannot open the file or directory\n");
        }
        else
        {
            while(fgets(filedata,sizeof(filedata),filePointer) != NULL)
            {
                filedata[strlen(filedata)-1] = '\0';
                if(strncmp(filedata,"State:",6) == 0)
                {
                //    printf("sdfghjk\n");
                    p = filedata + 7;
                    while(isspace(*p)==1)
                    {
                        ++p;
                    }
                    break;   
                }
            }

            if(p[0] == 'S')
            {
                printf("[%d] Running %s [%d]\n",jobid,job_array[i].process_name,job_array[i].process_id);
            }
            else if(p[0] == 'T')
            {
                printf("[%d] Stopped %s [%d]\n",jobid,job_array[i].process_name,job_array[i].process_id);
            }
        }
        fclose(filePointer);
    }
}