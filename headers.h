#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<time.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>
#include<wait.h>
#include<signal.h>
#include<ctype.h>

struct jobs
{
    int process_id;
    char process_name[10000];

}jobs;
struct jobs job_array[10000];

int universal;
int iterator,childpid,shellid,current_fore_id;
char user[1000],current_fore_process[1000]; //to print on the prompt
char cd_present_path[PATH_MAX];  //to store the pwd of the ./a.out
char presentpath_a_out[PATH_MAX];  //to store the pwd of the ./a.out
char tilda_handle[PATH_MAX];

void command_check_func(char *array[],int length);

void cd_func(char *path[], int length);

void pwd_func();

void ls_func(char *flags[],int length);
void updateforls(char tilda[100]);

void echo_func(char *sentence[], int length);

void setenv_func(char *array[], int length);
void unsetenv_func(char *array[], int length);

void back_fore_process(char *process[], int length);
void handler(int sig);

void kjob_func(char *command_process[]);

void overkill_func();

void jobs_func();

void fg_func(char *command_name[],int length);

void bg_func(char *command_name[],int length);

void ctrl_c(int sig);

void ctrl_z(int sig);

void pinfo_func(char *pid);