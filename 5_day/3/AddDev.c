#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd;
	int num[2]; // initialize two integer to accept the values from user
	int result;
	printf("Enter two number for addition operation: ");
	scanf("%d %d",&num[0],&num[1]); 

	fd = open("/dev/AddDev",O_RDWR,0777); // open the device with flag and permission
	if(fd < 0) //condition to check whether open is successful or not
	{
		printf("Not able to open the device\n");
		return -1;
	}

	write(fd,num,sizeof(num)); // write system call to write two numbers to kernel space
	read(fd,&result,sizeof(result)); // read system call to read the answer from kernel space
	printf("the result of addtion from kernel: %d\n",(int)result); // print the result coming from the kernel space with typecast
	close(fd); // close system call
	return 0;
}
