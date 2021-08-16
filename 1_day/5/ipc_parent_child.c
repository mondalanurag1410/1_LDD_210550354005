/*creating a child process and communicate between parent and child*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#define SIZE 20 //defin macro


int main()
{
    pid_t id;
    char buff[SIZE];
    int pd[2];
    pipe(pd); //making a pipe betwwen two process, as pipe is unidirectional
    	      //zero index is resposible for reading
	      //one index is responsible for writing
    id = fork(); //making child process

    if(id == 0) // condition to cheak: is child process or parent process
    {
        printf("Child\n");
        close(pd[1]); //close the write index as child wants to read from the parent
        read(pd[0],buff,SIZE);//the data from the parent read by the child
        printf("The data that received from parent: %s",buff);
        close(pd[0]); 
    }
    else
    {
        printf("Parent\n");
        close(pd[0]); //close the read index as this is the part of parent so have to write
        write(pd[1],"DESD\n",5); //write to the child process
        close(pd[1]);
    }

    return 0;
}
