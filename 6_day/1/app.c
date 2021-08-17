#include <sys/types.h> // for open, read write and close system call
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "ioctl_jif.h"

int main()
{
	int fd;
	char k_rd_buff[50];
	int delay_min; // take delay amount from user
	ssize_t result; // find the return value from the read system call
	printf("how much delay you want in second: ");
	scanf("%d",&delay_min);
	fd = open("/dev/MyCharDevice",O_RDWR,0777); // open the device with flag and permission
	if(fd < 0) // condition to check whether open successfully done or not
	{
		printf("not able to open the device\n");
		return -1;
	}
	printf("Ther data we got from the kernel is:\n\n");
	result = read(fd,k_rd_buff,50); // initiate read system call
	ioctl(fd,DATA_DELAY,delay_min);
	while(result != 16)
	{
		continue;
	}
	printf("%s\n",k_rd_buff); // print the data from the kernel space
	close(fd); // close system call
	return 0;
}
