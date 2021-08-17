/*Write a character driver with open, read, write and close functionalities. 
 * Test the driver through a user application by reading 
 * data from the driver and writing data to the driver*/

#include <linux/cdev.h> // for cdev structure
#include <linux/fs.h> //for unregitering the device driver
#include <linux/kdev_t.h> // for register device driver
#include <linux/types.h> // for regiter the device driver
#include <linux/init.h> // for module initialization
#include <linux/module.h> // for module exit function
#include <linux/uaccess.h>
#include "ioctl_jif.h"
#include <linux/jiffies.h>

//#define HZ 1000
/*function declaration*/
int my_open_fn(struct inode *inode, struct file *file_d);
int my_release_fn(struct inode *inode,struct file *file_d);
ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp);
long my_ioctl_fn(struct file *file_d,unsigned int cmd,unsigned long arg);

static char k_buff[100];
static int delay_trigger = 0;
/*file operation structure which function we expect in driver*/
struct file_operations op ={
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.read = my_read_fn,
	.unlocked_ioctl = my_ioctl_fn,
	.release = my_release_fn,
};
/*open function defination*/
int my_open_fn(struct inode *inode, struct file *file_d)
{
	printk("My device is using My charcter driver\n");
	return 0;
}
/*ioctl function*/
long my_ioctl_fn(struct file *file_d, unsigned int cmd,unsigned long arg)
{
	char *p = "data from kernel";
	int i =0;
	unsigned long timeout;
	timeout = jiffies + (arg * HZ); //determine the amount of delay user want using jiffies
	while(time_before(jiffies,timeout)) // condition that current jiffies value is higher that timeout 
					    //or not if not then contiture while loop
	{
		continue;
	}
	while(p[i] != '\0')
	{
		*(k_buff+i) = p[i];
		i++;
	}
	k_buff[i] = '\0';
	printk("the data send from kernel to user: %s\n",k_buff);
	delay_trigger++;
	return 0;
}

/*Read function defination*/
ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp)
{
	int re,i = 0;
	ssize_t amtdata;
	printk("data got for send to user is: %s\n",k_buff);
	while(k_buff[i] != '\0') // find the size of kernel buffer thet user wnat to read
	{
		i++;
	}
	printk("total length of data is: %d\n",i);
	if(delay_trigger == 1)
	{	
		re = copy_to_user(u_buff,(const char *)k_buff, i);

		if(re >= 0) //condition to check read done successfully done or not
		{	
			printk("total data successfully copy from kernel to user\n");
			amtdata = i;
			delay_trigger = 0;
			return amtdata;
		}
		else
		{
			printk("error in reading\n");
			delay_trigger = 0;
			return -1;
		}
	}
	return amtdata;
}

/*release function defination*/
int my_release_fn(struct inode *inode, struct file *file_d)
{
	printk("my device in now logging off\n");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
struct cdev *MyCharDevice;

dev_t my_driver_no;
///////////////////////////////////////////////////////module initialization function defination
static int my_driver_mod_init(void)
{
	int major,minor;
	my_driver_no = MKDEV(255,0); // make the device number
	/*macro to find the minor and mojor number*/
	major = MAJOR(my_driver_no);
	minor = MINOR(my_driver_no);
	
	printk("module logging in\n");

	int res = register_chrdev_region(my_driver_no,1,"MyCharDriver"); // statically register the device number

	if(res < 0) // condition to checkwhether registration successfully done or not
	{
		printk("\nDriver not allocated with driver number\n");
		return -1;
	}

	printk("my charcter driver got the region with major no %d and minor no %d\n",major,minor);
	printk("\nFor use the driver, driver expect the device having the following name:\nMyCharDevice\n");
	MyCharDevice = cdev_alloc();
	MyCharDevice->ops = &op; // pinting to the file structure object address

	int result = cdev_add(MyCharDevice,my_driver_no,1);

	if(result < 0) // condition to check whether device is successfully add or not
	{
		printk("Driver not recognised by kernel\n");
		return -1;
	}

	return 0;
}
//////////////////////////////////////////////////////////////////module exit fuction
static void my_driver_mod_exit(void)
{
	printk("module going to be logging off\n");
	unregister_chrdev_region(my_driver_no,1);
	printk("Driver now unregister\n");
	cdev_del(MyCharDevice);
	printk("kernel forgot my chracter driver\n");
}


module_init(my_driver_mod_init);
module_exit(my_driver_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("charter driver linux kerner module");
