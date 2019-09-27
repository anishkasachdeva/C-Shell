# Shell
## RUNNING THE SHELL

run `make` to generate the executable

run `./a.out` to run the shell

run `exit` to exit the shell


## FEATURES

#### Foreground processes
- The shell waits for the current process to execute

#### Background processes
- Use '&' at the end of any command to invoke a background process
- The process will then run in the background and when exited, a message will be displayed

#### ls command
- ls takes arguments as flags (as -<flagname>) and directories (as <directory name>)
- It lists the files of the directory mentioned. If no directory is mentioned, it lists the files in the current directory
- `ls` - lists in alphabetical order
- `ls -l` - long list
- `ls -a` - display hidden files
- `ls -al/-la` - long list including hidden files

#### cd command
- `cd <absolute path>` - goes to absolute path
- `cd` - goes to ~/
- `cd ~/<pathname>` - goes to ~/<pathname>
- `cd ..` - goes to previous directory
- `cd .` - stays in the same directory

#### echo command
- `echo` - prints empty line
- `echo text` - prints text

#### pwd command
- `pwd` - prints absolute path of current directory

#### pinfo command
- `pinfo` - prints process info of the shell
- `pinfo <pid>` - prints process info of given pid
  
#### Environment variables
- The shell inherits environment variables from the parent 
- `getenv` - used to get the username

#### exit command
- `exit` - exit the shell. The shell exits only when quit is typed

#### Redirection 
- Output of running one (or more) commands must be redirected to a file.

#### Set unset environment variables
- The shell inherits environment variables from the parent 
- `setenv var [value]` - ​ If environment variable ​ var does not exist, then it will create it.
- `unsetenv var` - ​it will destroy the environment variable ​ var.

#### User define command
- `jobs` - prints a list of all currently running jobs along with their pid.
- `​ kjob <jobNumber> <signalNumber>` - takes the job id of a running job and sends a signal value to that process.
- `​​ fg <jobNumber>` -brings a running or a stopped background job with given job number to foreground.
`​​ bg <jobNumber>` - changes a stopped background job to a running background job.
- ​ `overkill` - ​ kills all background process at once.
- ​ `CTRL-Z` ​- It should change the status of currently running job to stop, and push it in background process
- ​ `CTRL-C` ​ : It should cause a SIGINT signal to be sent to the current foreground job of your shell​ .
- ​ `​ Cronjob` ​ : executes a particular command in fixed time interval for a certain period.
