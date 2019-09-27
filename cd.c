#include "headers.h"

void cd_func(char *path[], int length)
{
    char str[1000],new[1000];
    for(int m=0;m<1000;m++)
    {
        user[m] = '\0';
        str[m] = '\0';
        new[m] = '\0';
    }
    int flag = 0;
    if(length == 1)
    {
        if(chdir(presentpath_a_out) == -1)
        {
            perror("chdir");
        }
        strcpy(user,"~");
    }
    else
    {
        strcpy(new,path[1]);
        if(path[1][0] == '~')
        {
            strcpy(str,presentpath_a_out);
            for(int i = 1; i < strlen(new); i++)
            {
                flag = 1;
                break;
            }
            if(flag == 1)
            {
                strcat(str,&path[1][1]);
                strcpy(cd_present_path,str);
                if(chdir(cd_present_path) == -1)
                {
                    perror("chdir");
                    strcpy(user,"~");
                }
                else
                {   
                    strcpy(user,"~");
                    strcat(user,&path[1][1]);
                }
            }
            else
            {
                if(chdir(presentpath_a_out) == -1)
                {
                    perror("chdir");
                    strcpy(user,"~");
                }
            }
        }
        else if(strcmp(path[0] ,"cd") == 0 && (path[1] == '\0'))
        {
            if(chdir(presentpath_a_out) == -1)
            {
                perror("chdir");
                strcpy(user,"~");
            }
        }
        else
        {
            int check = 0,i;
            
            if(chdir(path[1]) == -1)
            {
                perror("chdir");
            }
            getcwd(cd_present_path,sizeof(cd_present_path));
            if(strcmp(cd_present_path,presentpath_a_out) == 0)
            {
                strcpy(user,"~");
            }
            else
            {
                for(i = 0; i <= strlen(presentpath_a_out); i++)
                {
                    if(cd_present_path[i] != presentpath_a_out[i])
                    {
                        check = 1;
                        break;
                    }
                }
                if(check == 1)
                {
                    if(i < strlen(presentpath_a_out)) 
                    {
                        strcpy(user,cd_present_path);
                    }
                    else if(check == 1)
                    {
                        strcpy(user,"~");
                        strcat(user,&cd_present_path[i]);
                    }
                }
            }
        }
    }
}
