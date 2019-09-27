#include"headers.h"

void pwd_func()
{
    char pwd[PATH_MAX];
    if(getcwd(pwd,sizeof(pwd)) == NULL)
    {
        perror("getcwd");
    }
    printf("%s\n",pwd);
}
