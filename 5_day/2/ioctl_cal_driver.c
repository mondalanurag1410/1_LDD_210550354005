/*header files*/
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include "ioctl_cal_head.h" //header file for ioctl macro definations

/*function declaration*/
int my_open_fn(struct inode *inode, struct file *file_ioctl);
int my_release_fn(struct inode *inode, struct file *file_ioctl);
long my_ioctl_fn(struct file *file_ioctl,unsigned int cmd, unsigned long arg );

/*file operation structure*/
struct file_operations calop=
{
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.unlocked_ioctl = my_ioctl_fn,
	.release = my_release_fn,
};

/*structure that contains two integer on whinch we want the operation and one character taking
 * as symbol to represent what operation we ginna perform on the given interger. this is a 
 * replica that present in the user space program which contain the the user given data*/
struct operator
{
	int num1;
	int num2;
	char operation;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*open file operation structure defination*/
int my_open_fn(struct inode *inode, struct file *file_ioctl)
{
	printk("ioctl device using ioctl cal driver\n");
	return 0;
}
/*ioctl file operation defination*/
long my_ioctl_fn(struct file *file_ioctl, unsigned int cmd,unsigned long arg) // here only single ioctl command taken from the user
{
	int op1,op2;
	struct operator *data; //initialize an object of structure mentioned above
	char u_buff[20];
	char option;
	data = (struct operator *)u_buff; //typecast the user buffer with structure object, 
	                                  //so that the string data coming from user store in the
					  //u_buff as string and then typecast that sring into
					  //structure object
	copy_from_user(u_buff,(struct operator *)arg,sizeof(struct operator)); //copy from user as string into u_buff
	/*take the structure members in the local variable to perform certaion operations*/
	op1 = data->num1;
	op2 = data->num2;
	option = data->operation;

	/*if else ladder to perform the operation depends on 
	 * the operation structure member data provided 
	 * by user from user space to perform certain operations*/
	if(option == '+')
	{
		printk("Addition operation begin\n");
		int add_result = op1 + op2;
		printk("the result of addtion: %d\n",add_result);
		return 0;
	}
	else if(option == '-')
	{
		printk("Subtraction operation begin\n");
		int sub_result = op1-op2;
		printk("the result of subtraction: %d\n",sub_result);
		return 0;
	}
	else if(option == '*')
	{	
		printk("multiplication operation begin\n");
		int mul_result =  op1*op2;
		printk("the result of multiplication: %d\n",mul_result);
		return 0;
	}
	else if(option == '/')
	{	
		printk("division operation begin\n");
		int div_result = op1/op2;
		printk("the result of division: %d\n",div_result);
		return 0;
	}
	else
	{
		printk("invalid option\n");
		return -1;
	}
	return 0;
}
/*release function defination*/
int my_release_fn(struct inode *inode, struct file *file_ioctl)
{
	printk("the ioctl device now logg off from ioctl cal driver\n");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct cdev *MyIoctlCalDevice;
dev_t ioctl_cal_dn;
/*module init function defination*/
static int ioctl_driver_on(void)
{
	printk("welcome to ioctl based calculator driver module\n");
	int reg_result;
	int major,minor;
	reg_result = alloc_chrdev_region(&ioctl_cal_dn,0,1,"MyIoctlCalDriver"); //dynamically allocate
										//device number by the kernel space
	if(reg_result < 0) //condition to check whether kernel able to provide device number or not
	{
		printk("Driver not allocated any region by kernel\n");
		return -1;
	}
	/*finding major and minor number by using macro*/
	major = MAJOR(ioctl_cal_dn);
	minor = MINOR(ioctl_cal_dn);

	printk("the driver is allocated region by the kernel with major number: %d and minor number: %d\n",major,minor);
	/*allocate chacter device to do certain operations dynamically*/
	MyIoctlCalDevice = cdev_alloc();
	MyIoctlCalDevice->ops = &calop;

	int chdev_add_result = cdev_add(MyIoctlCalDevice,ioctl_cal_dn,1);
	if(chdev_add_result <0) // condition to check whether kenel able to add the character device or not
	{
		printk("the device is not added by kernel\n");
		return -1;
	}
	return 0;
}
/*module exit function defination*/
static void ioctl_driver_off(void)
{
	printk("your ioctl cal driver is about to log off from kernel space\n");
	cdev_del(MyIoctlCalDevice); // macro for delete the allocated space for charcter device
	printk("the ioctl cal device logged off\n");
	unregister_chrdev_region(ioctl_cal_dn,1); //unregister charcter device region
	printk("the ioctl cal driver unregister\nthank you\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*macro for module init and exit functions*/
module_init(ioctl_driver_on);
module_exit(ioctl_driver_off);

MODULE_LICENSE("GPL"); //general license
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("day5: q1: ioctl based calculator character driver LKM");
