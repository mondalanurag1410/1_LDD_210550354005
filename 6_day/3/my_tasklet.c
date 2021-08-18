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
#include <linux/interrupt.h>

/*function declaration*/
int my_open_fn(struct inode *inode, struct file *file_d);
int my_release_fn(struct inode *inode,struct file *file_d);
ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp);
void tasklet_fn(unsigned long data);

struct tasklet_struct my_tasklet; //make a structure object

static char k_buff[100];
/*file operation structure which function we expect in driver*/
struct file_operations op ={
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.read = my_read_fn,
	.release = my_release_fn,
};

/*tasklet function*/
void tasklet_fn(unsigned long data)
{
	int i =0;
	char *p = "data from kernel";
	//printk("add: %d",p);
	while(p[i] != '\0')
	{
		k_buff[i] = p[i];
		i++;
	}
	k_buff[i] = '\0';
		
}

		
/*open function defination*/
int my_open_fn(struct inode *inode, struct file *file_d)
{
	printk("My device is using My charcter driver\n");
	return 0;
}

/*read function defination*/
ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp)
{
	ssize_t amtdata;
	int i =0;
	tasklet_schedule(&my_tasklet); // schedule a tasklet
	while(k_buff[i] != '\0') 
		i++;
	printk("the length of the data: %d",i);
	int res = copy_to_user(u_buff,(const char *)k_buff,i); // copy the data to user
	if(res >= 0)
	{
		printk("copy to user done successfull\n");
		*k_buff = NULL; // makeig the data NULL
		printk("after delete all the data, now kernel buffer contains: %s\n",k_buff);
		amtdata = i;
		return amtdata;
	}
	else
	{
		printk("copy not done successfully\n");
		return -1;
	}
}

/*release fi=unction defination*/
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
	int data = 0;
	tasklet_init(&my_tasklet,(void *)tasklet_fn,(int)data); // initialize the tasklet
	tasklet_schedule(&my_tasklet); // schedule once
	return 0;
}
//////////////////////////////////////////////////////////////////module exit fuction
static void my_driver_mod_exit(void)
{
	printk("module going to be logging off\n");
	tasklet_kill(&my_tasklet);
	printk("tasklet kill\n");
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
