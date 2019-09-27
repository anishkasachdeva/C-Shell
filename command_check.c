#include "headers.h"

void command_check_func(char *array[],int length)
{
    if(strcmp(array[0],"quit") == 0)
    {
        exit(0);
    }
    else if(strcmp(array[0],"pwd") == 0)
    {
        pwd_func();
    }
    else if(strcmp(array[0],"ls") == 0)
    {

        ls_func(array,length);
    }
    else if(strcmp(array[0],"cd") == 0)
    {
            cd_func(array,length);
    }
    else if(strcmp(array[0],"echo") == 0)
    {
        echo_func(array, length);
    }
    else if(strcmp(array[0],"pinfo") == 0)
    {
        int pid = getpid();
        char pid_array[20];
        sprintf(pid_array,"%d",pid);
        if(length == 1)
        {
            pinfo_func(pid_array);
        }
        else
        {
            pinfo_func(array[1]);
        }
    }
    else if(strcmp(array[0],"overkill")==0)
    {
        overkill_func();
    }
    else if(strcmp(array[0],"jobs") == 0)
    {
        jobs_func();
    }
    else if(strcmp(array[0],"kjob") == 0)
    {
        kjob_func(array);
    }
    else if(strcmp(array[0],"fg") == 0)
    {
        fg_func(array,length);
    }
    else if(strcmp(array[0],"bg") == 0)
    {
        bg_func(array,length);
    }
    else if(strcmp(array[0],"setenv") == 0)
    {
        setenv_func(array,length);
    }
    else if(strcmp(array[0],"unsetenv") == 0)
    {
        unsetenv_func(array,length);
    }
    else
    {
        back_fore_process(array,length);
    }
}
