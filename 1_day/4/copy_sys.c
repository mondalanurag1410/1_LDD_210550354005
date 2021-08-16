/*write data to a text file read that data and copy the content
 * to another text file*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int opfd; // open file descriptor
    char buff[19];
    opfd = open("data.txt",O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); //open one text file using
    								 //create and read write flag enabling
								 //and provide the permission read and write
								 //permission
    if(opfd<0) //condition to check whether the open successfil or not
    {
	    printf("error opening the file\n");
	    return -1;
    }

    write(opfd,"My name is anurag\n",19); // call write system call with data to be write and size
    close(opfd);//close the read file descriptor

    int op_again;
    int op_new;

    op_again = open("data.txt",O_RDONLY); //read data from available text file
    if(op_again<0)
    {
	    printf("error in opening\n");
	    return -1;
    }
    
    read(op_again,buff,19); // store the data to the buffer
    printf("data: %s",buff);
    close(op_again);

    op_new = open("data_copy.txt",O_CREAT | O_WRONLY, S_IRUSR); //open a new text file 
    								//with flags and permissions where data
								//have to copy
    if(op_new<0) //condition for checking whether open successfully done or not
    {
	    printf("error in opening text file\n");
	    return -1;
    }
    
    write(op_new,buff,sizeof(buff)); //call write system call
    close(op_new); //close file descriptor
    return 0;

}
