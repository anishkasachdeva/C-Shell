#include "headers.h"

void setenv_func(char *array[], int length)
{
    if(length == 3)
    {
        setenv(array[1],array[2],1);
    }
    else if(length == 2)
    {
        setenv(array[1]," ",1);
    }
    else
    {
        printf("dfgh\n");
        return;
    }
    return;
}

void unsetenv_func(char *array[], int length)
{
    if(length !=2)
    {
        printf("ftghjnkm\n");
        return;
    }
    unsetenv(array[1]);
    return;
}