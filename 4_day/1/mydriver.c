/*Write a character driver with open and close functionality. 
 * Test the driver by writing an application that opens and closes the device driver. 
 * When open or closed, the open and close calls in the driver should be executed.*/

#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>


/*declaration of functions*/
int my_open_fn(struct inode *inode, struct file *file_d);
int my_release_fn(struct inode *inode,struct file *file_d);

/*the file operation structure which device have to perform*/
struct file_operations op ={
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.release = my_release_fn,
};
/*open function defination*/
int my_open_fn(struct inode *inode, struct file *file_d)
{
	printk("My device is using My charcter driver\n");
	return 0;
}

/*close function defination*/
int my_release_fn(struct inode *inode, struct file *file_d)
{
	printk("my device in now logging off\n");
	return 0;
}


/////////////////////////////////////////////////////////////////////////////////
struct cdev *MyCharDevice;

dev_t my_driver_no;
////////////////////////////////////////////////////////////////////module initialization function
static int my_driver_mod_init(void)
{
//	dev_t my_driver_no;
	int major,minor;
	my_driver_no = MKDEV(255,0); // making the device number
	major = MAJOR(my_driver_no); // finding the major number
	minor = MINOR(my_driver_no); // macro for finding the minor number
	
	printk("module logging in\n");

	int result = register_chrdev_region(my_driver_no,1,"MyCharDriver"); //statically making the device driver

	if(result < 0) // condition to check whether registration of done or not
	{
		printk("\nDriver not allocated with driver number\n");
		return -1;
	}

	printk("my charcter driver got the region with major no %d and minor no %d\n",major,minor);
	printk("\nFor open and write operation the driver expect the flloing device:\nMyCharDevice\n");
	MyCharDevice = cdev_alloc(); // allocation of the my cal device
	MyCharDevice->ops = &op;

	result = cdev_add(MyCharDevice,my_driver_no,1); //add the character device by kernel

	if(result < 0) // condition to check whether device is add or not
	{
		printk("Driver not recognised by kernel\n");
		unregister_chrdev_region(my_driver_no,1);
		return -1;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////module exit function
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
