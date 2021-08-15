#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd;
	fd = open("/dev/MyCharDevice",O_RDWR,777); // open system call with flag and permission
	if(fd < 0) //condition to check whether open successfully done or not
	{
		printf("not able to open the device\n");
		return -1;
	}
	close(fd); // close system call
	return 0;
}
