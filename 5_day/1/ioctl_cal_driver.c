/*Write a character driver that implements the ioctl functionality 
 * to demonstrate the calculator functionality. The user application 
 * should take input from the user and pass corresponding operations - ‘+’,’-‘,’*’,’/’ 
 * to the kernel module using ioctl. Based on the operation, 
 * ioctl should perform the add, sub, mul and div functions 
 * and print results in the kernel*/

#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include "ioctl_cal_head.h"


/*funtion declaration*/
int my_open_fn(struct inode *inode, struct file *file_ioctl);
int my_release_fn(struct inode *inode, struct file *file_ioctl);
long my_ioctl_fn(struct file *file_ioctl,unsigned int cmd, unsigned long arg );
//////////////////////////////////////////////////////////////////
/*file operation structure*/
struct file_operations calop=
{
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.unlocked_ioctl = my_ioctl_fn,
	.release = my_release_fn,
};
/*operator structure used to store data that is pointed by the address resided in arg*/
struct operator
{
	int num1;
	int num2;
};
/*initilization function defination*/
int my_open_fn(struct inode *inode, struct file *file_ioctl)
{
	printk("ioctl device using ioctl cal driver\n");
	return 0;
}
/*defination of ioctl function*/
long my_ioctl_fn(struct file *file_ioctl, unsigned int cmd,unsigned long arg)
{
	int op1,op2;
	struct operator *data;
	char u_buff[20];
	data = (struct operator *)u_buff; //typer cast the u_buff to the structure pointer
	copy_from_user(u_buff,(struct operator *)arg,sizeof(struct operator)); // copy whole data to u_buff from arg
	op1 = data->num1;
	op2 = data->num2;
	switch(cmd) // finding comman and according to that perform
	{
		case ADD:printk("Addition operation begin\n");
			 int add_result = op1 + op2;
			 printk("the result of addtion: %d\n",add_result);
			 return 0;
			 break;
		case SUB:printk("Subtraction operation begin\n");
			 int sub_result = op1-op2;
			 printk("the result of subtraction: %d\n",sub_result);
			 return 0;
			 break;
		case MUL:printk("multiplication operation begin\n");
			 int mul_result =  op1*op2;
			 printk("the result of multiplication: %d\n",mul_result);
			 return 0;
			 break;
		case DIV:printk("division operation begin\n");
			 int div_result = op1/op2;
			 printk("the result of division: %d\n",div_result);
			 return 0;
			 break;
		default:printk("invalid option\n");
			return -1;
			break;
	}
	return 0;
}
/*defination of release function*/
int my_release_fn(struct inode *inode, struct file *file_ioctl)
{
	printk("the ioctl device now logg off from ioctl cal driver\n");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
struct cdev *MyIoctlCalDevice; // pionter to the cdev structure
dev_t ioctl_cal_dn;
////////////////////////////////////////////////////////////////////////////////////
static int ioctl_driver_on(void)
{
	printk("welcome to ioctl based calculator driver module\n");
	int reg_result;
	int major,minor;
	reg_result = alloc_chrdev_region(&ioctl_cal_dn,0,1,"MyIoctlCalDriver"); // dymanic registration of device number
	if(reg_result < 0)
	{
		printk("Driver not allocated any region by kernel\n");
		return -1;
	}
	/*finding of major and minor number*/
	major = MAJOR(ioctl_cal_dn); 
	minor = MINOR(ioctl_cal_dn);
	printk("the driver is allocated region by the kernel with major number: %d and minor number: %d\n",major,minor);
	printk("\nFor ioctl based calculator driver, driver expected the following device:\nMyIoctlCalDevice\n");

	MyIoctlCalDevice = cdev_alloc();
	MyIoctlCalDevice->ops = &calop; //pionting to the file operation specified to the character device

	int chdev_add_result = cdev_add(MyIoctlCalDevice,ioctl_cal_dn,1); // additon of character device
	if(chdev_add_result <0)
	{
		printk("the device is not added by kernel\n");
		return -1;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////
/*module exit function*/
static void ioctl_driver_off(void)
{
	printk("your ioctl cal driver is about to log off from kernel space\n");
	cdev_del(MyIoctlCalDevice); // delete the allocation for character driver
	printk("the ioctl cal device logged off\n");
	unregister_chrdev_region(ioctl_cal_dn,1); // unregister the region defined by the character device
	printk("the ioctl cal driver unregister\nthank you\n");
}

module_init(ioctl_driver_on);
module_exit(ioctl_driver_off);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("day5: q1: ioctl based calculator character driver LKM");
