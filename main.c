#include "headers.h"

int main(void)
{
    iterator = 1;
    childpid = -1;
    shellid = 0;
    universal = 0;

    getcwd(cd_present_path,sizeof(cd_present_path));
    strcpy(presentpath_a_out,cd_present_path);
    if(strcmp(cd_present_path,presentpath_a_out)==0)
    {
        strcpy(user,"~");
    }

    char hostname[1024];
    hostname[1023] = '\0';

    char* username = getenv("USER");

    gethostname(hostname,sizeof(hostname)); //to get the hostname

signal(SIGCHLD,handler);
signal(SIGINT, ctrl_c);
signal(SIGTSTP, ctrl_z);

shellid =  getpid();


    while(1)
    {
        printf(">%s@%s:%s$ ",username,hostname,user);
        //printf("iterator %d\n", iterator);
/*if(universal == 1)
{
    iterator --;
    universal = 0;
}*/

        char *command_argument; 
        size_t bufsize = 10000, characters;
        command_argument = (char *)malloc(bufsize * sizeof(char));

        if(command_argument == NULL)
        {
            perror("Unable to allocate buffer\n");
        }
        getline(&command_argument,&bufsize,stdin); //to store the command line argument in command_argument character array

//add_command(command_argument);

        int tokens_size = 0;
        char dilimiter1[] = ";" ;
        char *semicolon[1000];
        char *ptr_copy1 = strtok(command_argument,dilimiter1); //to split the string on the basis of the space encountered
        while(ptr_copy1!=NULL)
        {
            semicolon[tokens_size++] = ptr_copy1;
            ptr_copy1 = strtok(NULL,dilimiter1);
        }
        //int orgin = dup(STDIN_FILENO);
        //int orgout =dup(STDOUT_FILENO);

        for(int token = 0;token < tokens_size; token++)
        {
            
            int size = 0;
            char delimiter2[] = "|\n" ;
            char *pipeline[1000];
            char *ptr_copy2 = strtok(semicolon[token],delimiter2); //to split the string on the basis of the space encountered
            while(ptr_copy2!=NULL)
            {
                pipeline[size++] = ptr_copy2;
                ptr_copy2 = strtok(NULL,delimiter2);
            }

            int mypipe1[2],mypipe2[2];
            int num_of_pipes=0;
            num_of_pipes = size -1;

            for(int i = 0; i < size; i++)
            {
                int orgin = dup(STDIN_FILENO);
                int orgout =dup(STDOUT_FILENO);
            //    printf("value of i %d\n",i);
                int num = 0;
                char dilimiter3[] = " \n\r\t";
                char *array[1000];
                

                

                char *ptr_copy3 = strtok(pipeline[i],dilimiter3); //to split the string on the basis of the space encountered
                while(ptr_copy3!=NULL)
                {
                    array[num++] = ptr_copy3;
                    ptr_copy3 = strtok(NULL,dilimiter3);
                }
                int length_arg = num;




                int stdin,stdout,stdout_append,position_of_filein,position_of_fileout,position_of_fileapp;
                stdin=stdout=stdout_append=0;
                int fd1=-1,fd2=-1,fd_open=-1,fd_write=-1;
                for(int check = 0; check<length_arg;check++)
                {
                    if(strcmp(array[check],"<")==0)
                    {
                        stdin++;
                        position_of_filein = check;
                    }
                    if(strcmp(array[check],">")==0)
                    {
                        stdout++;
                        position_of_fileout = check;
                    }
                    if(strcmp(array[check],">>")==0)
                    {
                        stdout_append++;
                        position_of_fileapp = check;
                    }
                }

                               // printf("in%d\n",stdin);
                               // printf("out%d\n",stdout);
                               // printf("app%d\n",stdout_append);
                               // printf("%s\n",array[position_of_filein+1]);

                if(stdin > 0 && stdout == 0 && stdout_append == 0)
                {
                    //printf("fghjk\n");
                    fd1 = open(array[position_of_filein+1],O_RDONLY,S_IRWXU);
                    if(fd1 < 0)
                    {
                        perror("open");
                    }
                    dup2(fd1,0);
                    length_arg = position_of_filein;
             //       printf("******%d\n",length_arg);
                }
                else if(stdin == 0 && (stdout == 1 || stdout_append == 1))
                {
                    if(stdout == 1 && stdout_append == 0)
                    {
                        fd2 = open(array[position_of_fileout+1],O_WRONLY | O_CREAT | O_TRUNC,0644);
                        if(fd2 < 0)
                        {
                            perror("open");
                        }
                        dup2(fd2,1);
                        length_arg = position_of_fileout;
                        
                    }
                    else if(stdout == 0 && stdout_append == 1)
                    {
                        fd2 = open(array[position_of_fileapp+1],O_WRONLY | O_CREAT | O_APPEND,0644);
                        if(fd2 < 0)
                        {
                            perror("open");
                        }
                        dup2(fd2,1);
                        length_arg = position_of_fileapp;
                    }
                }
                else if(stdin == 1 && (stdout == 1 || stdout_append == 1))
                {
                    fd_open,fd_write;
                    fd_open = open(array[position_of_filein+1],O_RDONLY);
                    if(fd_open < 0)
                    {
                        perror("open");
                    }
                    if(stdout==1 && stdout_append == 0)
                    {
                        fd_write = open(array[position_of_fileout+1], O_WRONLY | O_CREAT | O_TRUNC,0644);
                    }
                    else if(stdout==0 && stdout_append == 1)
                    {
                        fd_write = open(array[position_of_fileapp+1], O_WRONLY|O_CREAT | O_APPEND,0644);
                    }
                    dup2(fd_open,0);
                    dup2(fd_write,1);
                    length_arg = position_of_filein;
                }
               // printf("in %d\n",position_of_filein);
               // printf("out %d\n",position_of_fileout);
              //  printf("app %d\n",position_of_fileapp);

                array[length_arg] = NULL;







               // printf("num of pipes %d\n",num_of_pipes); 
                if(num_of_pipes == 0)
                {
                    command_check_func(array,length_arg);
                }
                else
                {
                    if(i%2 !=0 )
                    {
                        int ret = pipe(mypipe1);
                        if(ret == -1)
                        {
                            perror("pipe");
                        }
                    }
                    else if(i%2 == 0)
                    {
                        int ret = pipe(mypipe2);
                        if(ret == -1)
                        {
                            perror("pipe");
                        }
                    }
                    int pid = fork();
                    if(pid == -1)
                    {
                        perror("Child process could not be created\n");
                    }
                    else if(pid == 0)
                    {
                        if(i == 0)
                        {
                            dup2(mypipe2[1],1);
                        }
                        else if(i == num_of_pipes)
                        {
                            if(num_of_pipes % 2 == 0) //even number of pipes
                            {
                            //    close(mypipe1[1]);
                                dup2(mypipe1[0],0);
                            }
                            else if(num_of_pipes % 2 != 0) //odd number of pipes
                            {
                            //    close(mypipe2[1]);
                                dup2(mypipe2[0],0);
                            }
                        }
                        else // when the command is in between two pipes
                        {
                            if(i % 2 == 0)
                            {
                            //    close(mypipe1[1]);
                            //    close(mypipe2[0]);
                                dup2(mypipe1[0],0);
                                dup2(mypipe2[1],1);
                            }   
                            else if(i % 2 != 0)
                            {
                            //    close(mypipe2[1]);
                            //    close(mypipe1[0]);
                                dup2(mypipe2[0],0);
                                dup2(mypipe1[1],1);
                            }
                        }
                       // array[length_arg] = NULL;
                        command_check_func(array,length_arg);
                        exit(0);
                    }
                    wait(NULL);
        //closing the modified read and write ends
                    if(i == 0)
                    {
                        close(mypipe2[1]);
                    //    printf("closed\n");
                    }
                    else if(i == tokens_size - 1)
                    {
                        if(num_of_pipes % 2 == 0) //even number of pipes
                        {
                            close(mypipe1[0]);
                        }
                        else if(num_of_pipes % 2 != 0) //odd number of pipes
                        {
                            close(mypipe2[0]);
                        }
                    }
                    else // when the command is in between two pipes
                    {
                        if(i % 2 == 0)
                        {
                            close(mypipe1[0]);
                            close(mypipe2[1]);
                        }   
                        else if(i % 2 != 0)
                        {
                            close(mypipe2[0]);
                            close(mypipe1[1]);
                        }
                    }
                    //wait(NULL);
                }
                if(fd1>0)
                {
                    close(fd1);
                }
                if(fd2>0)
                {
                    close(fd2);
                }
                if(fd_open>0)
                {
                    close(fd_open);
                }
                if(fd_write>0)
                {
                    close(fd_write);
                }
                dup2(orgin,0);
                dup2(orgout,1);
            }
        }
    }
    return 0;
}
