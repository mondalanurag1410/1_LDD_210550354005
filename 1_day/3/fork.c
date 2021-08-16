/*making child using fork system call*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t id; // initialize opaque data type for fork
    printf("Before ceating the child process\n");

    id = fork(); // calling fork system call

    if(id == 0) // condition to check whether it is a parent process or child process if zero the child
    {
        printf("In child process.\n");
        printf("The PID of the child process is: %d\n",getpid()); // find the PID for child process
        printf("The parent id of the child process is: %d\n",getppid()); // sending back the parent process id
        printf("The if value of child is: %d\n",id); // printing the return value from
       						     //the child procss and that must be zero
    }
    else
    {
        printf("In parent process.\n");
        printf("The PID of the parent process is: %d\n",getpid());
        printf("The parent id of the parent process is: %d\n",getppid());
        printf("The if value of parent is: %d\n",id); // return value must be child process id
    }

    return 0;
}
