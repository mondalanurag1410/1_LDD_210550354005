#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "my_ioctl.h"
#include <stdlib.h>

struct mystats
{
	int size;
	char buff[100];
	int r_w;
};

int main()
{
	int fd;
	struct mystats *app1_stat;
	char sta_app1[100];
	char *wr_buff = "data from user";
	app1_stat = (struct mystats *)malloc(sizeof(struct mystats));
	app1_stat = (struct mystats *)sta_app1;
	fd = open("/dev/app1",O_RDWR, 0777);
	if(fd < 0)
	{
		printf("error opening file\n");
		return -1;
	}
	write(fd,wr_buff,sizeof(wr_buff));
	ioctl(fd,GETSTATS,&sta_app1);
	printf("size of data received: %d\n",app1_stat->size);
	printf("data: %s\n",app1_stat->buff);
	printf("status: %d\n",app1_stat->r_w);
	//read(fd,rd_buff,100);
	close(fd);
	return 0;
}
