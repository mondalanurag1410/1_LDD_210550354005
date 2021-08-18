#include <sys/types.h> // for open, read write and close system call
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd;
	char k_rd_buff[50];
	fd = open("/dev/MyCharDevice",O_RDWR,0777); // open the device with flag and permission
	if(fd < 0) // condition to check whether open successfully done or not
	{
		printf("not able to open the device\n");
		return -1;
	}
	read(fd,&k_rd_buff,50); // read system call
	printf("the data the we got from kernel:\n\n%s\n",k_rd_buff); // print the data from the kernel space
	close(fd); // close system call
	return 0;
}
