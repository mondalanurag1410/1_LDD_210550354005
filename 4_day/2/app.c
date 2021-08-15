#include <sys/types.h> // for open, read write and close system call
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd, i =0;
	char k_rd_buff[50];
	char *k_wr_buff = "this data is writing from user to kernel";

	while(k_wr_buff[i] != '\0') // find the size of data which have to send to the kernel space
	{
		i++;
	}

	fd = open("/dev/MyCharDevice",O_RDWR,0777); // open the device with flag and permission
	if(fd < 0) // condition to check whether open successfully done or not
	{
		printf("not able to open the device\n");
		return -1;
	}
	write(fd,k_wr_buff,i); //write system call
	read(fd,k_rd_buff,50); // read system call
	printf("the data the we got from kernel:\n\n%s\n",k_rd_buff); // print the data from the kernel space
	close(fd); // close system call
	return 0;
}
