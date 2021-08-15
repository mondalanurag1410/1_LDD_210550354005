#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "ioctl_cal_head.h" // hr=eader where ioctl macros are declared

/*structure that take two interger and one character members from the user only
 * charcater input signifies which operation we have to do on the integers*/
struct operator
{
	int num1;
	int num2;
	char operator;
};
////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int fd, result;
	struct operator val;
	printf("Enter two number: ");
	scanf("%d %d",&val.num1,&val.num2); //takeing user interger inputs
	
	printf("Enter the operation you want to do:\n'+' : Addition\n'-' : Subtraction\n'*' : Multiplication\n'/' : Division\n\nEnter Now:  ");
	scanf(" %c",&val.operator); // taking operation input from user

	fd = open("/dev/MyIoctlCalDevice",O_RDWR,0777); //open device with read write and execute permission for all and with flag read and write
	if(fd<0) // condition to check whether user able to open the device or not
	{
		printf("not able to open the device\n");
		return -1;
	}
	
	ioctl(fd, OPERATION, &val); // ioctl comman with the command as macro initialized in the header file
	close(fd);
	return 0;
}
