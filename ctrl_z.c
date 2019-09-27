#include "headers.h"

void ctrl_z(int sig)
{
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname,sizeof(hostname));

    char* username = getenv("USER");

    /*printf("username %s\n",username);
printf("hostname %s\n",hostname);
printf("user %s\n",user);*/

    int pid = getpid();

    if(pid != shellid)
    {
        return;
    }
    if(childpid != -1)
    {
        kill(childpid, SIGTTIN);
        kill(childpid, SIGTSTP);
        //printf("ADDING IN JOBS %s \n", current_fore_process);
        job_array[iterator].process_id = childpid;
        strcpy(job_array[iterator].process_name,current_fore_process);
        //printf("ittt bef%d\n", iterator);
        
        iterator++;
        //printf("ittt %d\n", iterator);
    }
    else
    {
        fflush(stdout);
    }
    signal(SIGTSTP, ctrl_z);






    //printf(">%s@%s:%s$ ",username,hostname,user);
    /*printf(">%s@%s:%s$ ",username,hostname,user);

        char *command_argument; 
        size_t bufsize = 10000, characters;
        command_argument = (char *)malloc(bufsize * sizeof(char));

        if(command_argument == NULL)
        {
            perror("Unable to allocate buffer\n");
        }
        getline(&command_argument,&bufsize,stdin); //to store the command line argument in command_argument character array*/
    fflush(stdout);
}
