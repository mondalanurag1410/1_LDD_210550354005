#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd;
	fd = open("/dev/MyCharDevice",O_RDWR,777);
	

	if(fd < 0)
	{
		printf("not able to open the device\n");
		return -1;
	}
	
	close(fd);
	return 0;
}
