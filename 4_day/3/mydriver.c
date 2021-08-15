/*Write a character driver to dynamically allocate a maj, min no pair from the kernel. 
 * and perform the raed write open and close functionality*/

#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>

int my_open_fn(struct inode *inode, struct file *file_d);
int my_release_fn(struct inode *inode,struct file *file_d);
ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp);
ssize_t my_write_fn(struct file *file_d, const char __user *u_buff, size_t count, loff_t *offp);

struct file_operations op ={
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.read = my_read_fn,
	.write = my_write_fn,
	.release = my_release_fn,
};

int my_open_fn(struct inode *inode, struct file *file_d)
{
	printk("My device is using My charcter driver\n");
	return 0;
}

ssize_t my_write_fn(struct file *file_d,const char __user *u_buff, size_t count, loff_t *offp)
{
	int re_wr;
	char k_wr_buff[100];
	ssize_t rdata;
	re_wr = copy_from_user((char *)k_wr_buff,u_buff,count);

	if(re_wr >= 0)
	{
		printk("write operation successfully done by user\n");
		printk("the data that write from user is:\n\n%s\n",k_wr_buff);
		rdata = count;
		return rdata;
	}
	else
	{
		printk("the write operation not successfully done.\n");
		return -1;
	}
}


ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp)
{
	const char *k_buff = "this data you are reading from kernel";
	int re,i = 0;
	ssize_t amtdata;
	while(k_buff[i] != '\0')
	{
		i++;
	}

	re = copy_to_user(u_buff,k_buff, i);

	if(re >= 0)
	{
		printk("total data successfully copy from kernel to user\n");
		amtdata = sizeof(k_buff);
		return amtdata;
	}
	else
	{
		printk("error in reading\n");
		return -1;
	}

}


int my_release_fn(struct inode *inode, struct file *file_d)
{
	printk("my device in now logging off\n");
	return 0;
}



struct cdev *MyCharDevice;

dev_t my_driver_no;

static int my_driver_mod_init(void)
{
	int major,minor;
	printk("module logging in\n");

	int res = alloc_chrdev_region(&my_driver_no,0,1,"MyCharDriver");
	
	major = MAJOR(my_driver_no);
	minor = MINOR(my_driver_no);

	if(res < 0)
	{
		printk("\nDriver not allocated with driver number\n");
		return -1;
	}

	printk("my charcter driver got the region with major no %d and minor no %d\n",major,minor);
	printk("\nFor successfully operate the driver expent the following device:\nMyCharDevice\n")
	MyCharDevice = cdev_alloc();
	MyCharDevice->ops = &op;

	int result = cdev_add(MyCharDevice,my_driver_no,1);

	if(result < 0)
	{
		printk("Driver not recognised by kernel\n");
		return -1;
	}
	return 0;
}

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
