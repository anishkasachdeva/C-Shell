#include "headers.h"

void ctrl_c(int sig)
{
    int pid = getpid();
    if(pid != shellid)
    {
        return;
    }
    if(childpid != -1)
    {
        kill(childpid,SIGINT);
        signal(SIGINT, ctrl_c);
    }
}