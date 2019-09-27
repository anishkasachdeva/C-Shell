#include "headers.h"

void pinfo_func(char *pid)
{
    char filedata[10000],path[10000],exe_path[10000],output[10000],*p;
    snprintf(path,sizeof(path), "/proc/%s/status" , pid);
    snprintf(exe_path,sizeof(exe_path),"/proc/%s/exe" , pid);
    readlink(exe_path , output , 1024);

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
            if(strncmp(filedata,"Pid:",4) == 0)
            {
                p = filedata + 5;
                while(isspace(*p)==1)
                {
                    ++p;
                }
                printf("Pid -- %s", p);
            }
            else if(strncmp(filedata,"State:",6) == 0)
            {
                p = filedata + 7;
                while(isspace(*p)==1)
                {
                    ++p;
                }
                printf("Process Status -- %s",p);
            }
            else if(strncmp(filedata,"VmSize:",7) == 0)
            {
                p = filedata + 8;
                while(isspace(*p)==1)
                {
                    ++p;
                }
                printf("Memory -- %s",p);
            }
        }
    }
    printf("Executable Path -- %s\n", output);
    fclose(filePointer);
}