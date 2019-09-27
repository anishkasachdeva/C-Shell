#include "headers.h"

void updateforls(char tilda[100])
{
    for(int m=0;m<PATH_MAX;m++)
    {
        tilda_handle[m] = '\0';
    }
    if(strlen(tilda) == 1 || strlen(tilda) == 2)
    {
        strcpy(tilda_handle,presentpath_a_out);
    }
    else
    {
        char new[strlen(tilda)-2];
        for(int i = 1;i < strlen(tilda); i++)
        {
            new[i-1] = tilda[i];
        }
        strcpy(tilda_handle,presentpath_a_out);
        strcat(tilda_handle,new);
    }
}




void ls_func(char *flags[],int length)
{
    for(int m=0;m<PATH_MAX;m++)
    {
        tilda_handle[m] = '\0';
    }

    int a = 0,l = 0 ,d = 0,len_directory,index_directory;
    for(int i = 1; i < length; i++)
    {
        if(flags[i][0] == '-')
        {
            for(int j = 1; j < strlen(flags[i]); j++)
            {
                if(flags[i][j] == 'l')
                {
                    l = 1;
                }
                else if(flags[i][j] == 'a')
                {
                    a = 1;
                }
            }
        }
        else
        {
            index_directory = i;
            d = 1;
            len_directory = strlen(flags[i]);
            if(flags[i][0] == '~')
            {
                updateforls(flags[i]);
            }
            else
            {
                strcpy(tilda_handle,presentpath_a_out);
                if(flags[i][0] == '/')
                {
                    strcat(tilda_handle,flags[index_directory]);
                }
                else
                {       
                    strcat(tilda_handle,"/");
                    strcpy(tilda_handle,flags[index_directory]);
                }
            }
        }
    }


    if(l == 0 && a == 0 && d == 0) //implementing ls
    {
        DIR *dir;
        struct dirent *read_dir;
        char dir_name[1] = ".";
        dir = opendir(dir_name);
        if(dir == NULL) //error handling
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {
        while((read_dir = readdir(dir)) !=NULL)
        {
            if(read_dir->d_name[0] != '.')
            {
                printf("%s\n",read_dir->d_name);
            }
        }
        }
        closedir(dir);
    }

    else if(l == 0 && a == 0 && d == 1) //implementing ls directory
    {
        DIR *dir;
        struct dirent *read_dir;
       // char dir_name[len_directory];
      //  strcpy(dir_name,flags[index_directory]);
        dir = opendir(tilda_handle);
        if(dir == NULL) //error handling
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {
            while((read_dir = readdir(dir)) !=NULL)
            {
                if(read_dir->d_name[0] != '.')
                {
                    printf("%s\n",read_dir->d_name);
                }
            }
        }
        closedir(dir);
    }

    else if(l == 0 && a == 1 && d == 0) //implementing ls -a
    {
        DIR *dir;
        struct dirent *read_dir;
        char dir_name[1] = ".";
        dir = opendir(dir_name);
        if(dir == NULL) //error handling
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {
            while((read_dir = readdir(dir)) !=NULL)
            {
                    printf("%s\n",read_dir->d_name);
            }
        }
        closedir(dir);
    }

    else if(l == 0 && a == 1 && d == 1) //implementing ls -a directory
    {
        DIR *dir;
        struct dirent *read_dir;
       // char dir_name[len_directory];
       // strcpy(dir_name,flags[index_directory]);
        dir = opendir(tilda_handle);
        if(dir == NULL) //error handling
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {
            while((read_dir = readdir(dir)) !=NULL)
            {
                    printf("%s\n",read_dir->d_name);
            }
        }
        closedir(dir);
    }

    else if(l == 1 && a == 1 && d == 0) //implementing ls -la
    {
        DIR *dir;
        struct dirent *read_dir;
        char dir_name[1] = ".";
        dir = opendir(dir_name);
        if(dir == NULL)
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {
            while((read_dir = readdir(dir)) != NULL)
            {
                struct stat filestat;
                stat(read_dir->d_name,&filestat);

                //1st column
                if(S_ISDIR(filestat.st_mode)) //prints whether a directory or a regular file 
                {
                    printf("d");
                }
                else
                {
                    printf("-");
                }

                printf( (filestat.st_mode & S_IRUSR) ? "r" : "-"); //to print the permissions of the file or directory
                printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
                printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (filestat.st_mode & S_IXOTH) ? "x " : "- ");

                //2nd column
                printf("%lu ",(filestat.st_nlink)); //to print the number of links

                //3rd column
                struct passwd *pw = getpwuid(filestat.st_uid);
                if(pw!=0)
                {
                    printf("%9s ",pw->pw_name);
                }

                //4th column
                struct group  *gr = getgrgid(filestat.st_gid);
                if(gr != 0)
                {
                    printf("%9s ",gr->gr_name);
                }

                //5th column
                printf("%6ld ",(filestat.st_size)); //to print the file size
                //6th column 
                char *time = ctime(&filestat.st_mtime); //to print the last modified date of the file
                if(time[strlen(time)-1] == '\n')
                {
                    time[strlen(time)-1] = '\0';
                }
                printf("%s ",time);

                //7th column
                printf("%s",read_dir->d_name); //to print the file name
                printf("\n");
            }
        }
        closedir(dir);
    }

    else if(l == 1 && a == 0 && d == 0) //implementing ls -l
    {
        DIR *dir;
        struct dirent *read_dir;
        char dir_name[1] = ".";
        dir = opendir(dir_name);
        if(dir == NULL)
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {
            while((read_dir = readdir(dir)) != NULL)
            {
                if(read_dir->d_name[0] != '.')
                {
                    struct stat filestat;
                    stat(read_dir->d_name,&filestat);

                    //1st column
                    if(S_ISDIR(filestat.st_mode)) //prints whether a directory or a regular file 
                    {
                        printf("d");
                    }
                    else
                    {
                        printf("-");
                    }

                    printf( (filestat.st_mode & S_IRUSR) ? "r" : "-"); //to print the permissions of the file or directory
                    printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (filestat.st_mode & S_IXOTH) ? "x " : "- ");

                    //2nd column
                    printf("%lu ",(filestat.st_nlink)); //to print the number of links

                    //3rd column
                    struct passwd *pw = getpwuid(filestat.st_uid);
                    if(pw!=0)
                    {
                        printf("%9s ",pw->pw_name);
                    }

                    //4th column
                    struct group  *gr = getgrgid(filestat.st_gid);
                    if(gr != 0)
                    {
                        printf("%9s ",gr->gr_name);
                    }

                    //5th column
                    printf("%6ld ",(filestat.st_size)); //to print the file size
                    //6th column 
                    char *time = ctime(&filestat.st_mtime); //to print the last modified date of the file
                    if(time[strlen(time)-1] == '\n')
                    {
                        time[strlen(time)-1] = '\0';
                    }
                    printf("%s ",time);

                    //7th column
                    printf("%s",read_dir->d_name); //to print the file name
                    printf("\n");
                }
            }
        }
        closedir(dir);
    }
    
    else if(l == 1 && a == 0 && d == 1) //implementing ls -l directory
    {
        DIR *dir;
        struct dirent *read_dir;
       // char dir_name[len_directory];
      //  strcpy(dir_name,flags[index_directory]);
        dir = opendir(tilda_handle);
        if(dir == NULL)
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {
            while((read_dir = readdir(dir)) != NULL)
            {
                if(read_dir->d_name[0] != '.')
                {
                    struct stat filestat;
                    stat(read_dir->d_name,&filestat);

                    //1st column
                    if(S_ISDIR(filestat.st_mode)) //prints whether a directory or a regular file 
                    {
                        printf("d");
                    }
                    else
                    {
                        printf("-");
                    }

                    printf( (filestat.st_mode & S_IRUSR) ? "r" : "-"); //to print the permissions of the file or directory
                    printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (filestat.st_mode & S_IXOTH) ? "x " : "- ");

                    //2nd column
                    printf("%lu ",(filestat.st_nlink)); //to print the number of links

                    //3rd column
                    struct passwd *pw = getpwuid(filestat.st_uid);
                    if(pw!=0)
                    {
                        printf("%9s ",pw->pw_name);
                    }

                    //4th column
                    struct group  *gr = getgrgid(filestat.st_gid);
                    if(gr != 0)
                    {
                        printf("%9s ",gr->gr_name);
                    }

                    //5th column
                    printf("%6ld ",(filestat.st_size)); //to print the file size
                    //6th column 
                    char *time = ctime(&filestat.st_mtime); //to print the last modified date of the file
                    if(time[strlen(time)-1] == '\n')
                    {
                        time[strlen(time)-1] = '\0';
                    }
                    printf("%s ",time);

                    //7th column
                    printf("%s",read_dir->d_name); //to print the file name
                    printf("\n");
                }
            }
        }
        closedir(dir);
    }

    else if(l == 1 && a == 1 && d == 1) //implementing ls -la directory
    {
        DIR *dir;
        struct dirent *read_dir;
      //  char dir_name[len_directory];
      //  strcpy(dir_name,flags[index_directory]);
        dir = opendir(tilda_handle);
        if(dir == NULL)
        {
            printf("ERROR : Unable to open the given directory\n");
        }
        else
        {

            while((read_dir = readdir(dir)) != NULL)
            {
                struct stat filestat;
                stat(read_dir->d_name,&filestat);

                //1st column
                if(S_ISDIR(filestat.st_mode)) //prints whether a directory or a regular file 
                {
                    printf("d");
                }
                else
                {
                    printf("-");
                }

                printf( (filestat.st_mode & S_IRUSR) ? "r" : "-"); //to print the permissions of the file or directory
                printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
                printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (filestat.st_mode & S_IXOTH) ? "x " : "- ");

                //2nd column
                printf("%lu ",(filestat.st_nlink)); //to print the number of links

                //3rd column
                struct passwd *pw = getpwuid(filestat.st_uid);
                if(pw!=0)
                {
                    printf("%9s ",pw->pw_name);
                }

                //4th column
                struct group  *gr = getgrgid(filestat.st_gid);
                if(gr != 0)
                {
                    printf("%9s ",gr->gr_name);
                }

                //5th column
                printf("%6ld ",(filestat.st_size)); //to print the file size
                //6th column 
                char *time = ctime(&filestat.st_mtime); //to print the last modified date of the file
                if(time[strlen(time)-1] == '\n')
                {
                    time[strlen(time)-1] = '\0';
                }
                printf("%s ",time);

                //7th column
                printf("%s",read_dir->d_name); //to print the file name
                printf("\n");
            }
        }
        closedir(dir);
    }
}
