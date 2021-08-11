#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>



int my_open_fn(struct inode *inode, struct file *file_d);
int my_release_fn(struct inode *inode,struct file *file_d);


struct file_operations op ={
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.release = my_release_fn,
};

int my_open_fn(struct inode *inode, struct file *file_d)
{
	printk("My device is using My charcter driver\n");
	return 0;
}


int my_release_fn(struct inode *inode, struct file *file_d)
{
	printk("my device in now logging off\n");
	return 0;
}



struct cdev *MyCharDriver;

dev_t my_driver_no;

static int my_driver_mod_init(void)
{
//	dev_t my_driver_no;
	int major,minor;
	my_driver_no = MKDEV(255,0);
	major = MAJOR(my_driver_no);
	minor = MINOR(my_driver_no);
	
	printk("module logging in\n");

	int result = register_chrdev_region(my_driver_no,1,"MyCharDriver");

	if(result < 0)
	{
		printk("\nDriver not allocated with driver number\n");
		return -1;
	}

	printk("my charcter driver got the region with major no %d and minor no %d\n",major,minor);

	MyCharDriver = cdev_alloc();
	MyCharDriver->ops = &op;

	result = cdev_add(MyCharDriver,my_driver_no,1);

	if(result < 0)
	{
		printk("Driver not recognised by kernel\n");
		unregister_chrdev_region(my_driver_no,1);
		return -1;
	}

	return 0;
}

static void my_driver_mod_exit(void)
{
	printk("module going to be logging off\n");
	unregister_chrdev_region(my_driver_no,1);
	printk("Driver now unregister\n");
	cdev_del(MyCharDriver);
	printk("kernel forgot my chracter driver\n");
}


module_init(my_driver_mod_init);
module_exit(my_driver_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("charter driver linux kerner module");
