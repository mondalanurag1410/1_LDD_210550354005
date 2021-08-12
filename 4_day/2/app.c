#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd, i =0;
	char k_rd_buff[50];
	char *k_wr_buff = "this data is writing from user to kernel";

	while(k_wr_buff[i] != '\0')
	{
		i++;
	}

	fd = open("/dev/MyCharDevice",O_RDWR,0777);
	

	if(fd < 0)
	{
		printf("not able to open the device\n");
		return -1;
	}
	write(fd,k_wr_buff,i);
	read(fd,k_rd_buff,50);
	printf("the data the we got from kernel:\n\n%s\n",k_rd_buff);
	close(fd);
	return 0;
}
