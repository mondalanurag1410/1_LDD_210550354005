#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "ioctl_cal_head.h"

struct operator
{
	int num1;
	int num2;
	char operator;
};

int main()
{
	int fd, result;
	struct operator val;
	printf("Enter two number: ");
	scanf("%d %d",&val.num1,&val.num2);
	
	printf("Enter the operation you want to do:\n'+' : Addition\n'-' : Subtraction\n'*' : Multiplication\n'/' : Division\n\nEnter Now:  ");
	scanf(" %c",&val.operator);

	fd = open("/dev/MyIoctlCalDevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("not able to open the device\n");
		return -1;
	}
	
	ioctl(fd, OPERATION, &val);
	close(fd);
	return 0;
}
