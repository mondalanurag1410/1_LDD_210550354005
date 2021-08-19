#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include "my_ioctl.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("exam q2");

int open_fn(struct inode *inode, struct file *filep);
int release_fn(struct inode *inode, struct file *filep);
long ioctl_fn(struct file *filep,unsigned int cmd, unsigned long arg );
ssize_t write_fn(struct file *filep,const char __user *u_buff,size_t count,loff_t *offp );
//ssize_t read_add(struct file *filep,char __user *u_buff, size_t count, loff_t *offp);

struct file_operations op=
{
	.owner = THIS_MODULE,
	.open = open_fn,
//	.read = read_fn,
	.write = write_fn,
	.release = release_fn,
	.unlocked_ioctl = ioctl_fn,
};

static struct mystatus
{
	int size;
	char buff[100];
	int r_w;
};
static struct mystatus *data;


int open_fn(struct inode *inode, struct file *filep)
{
	printk("ioctl device using ioctl driver\n");
	return 0;
}

ssize_t write_fn(struct file *filep, const char __user *u_buff, size_t count, loff_t *offp)
{
	int result = copy_from_user((char *)data->buff,u_buff,count);
	ssize_t rdata;
	if(result == 0)
	{
		printk("copy from user done\n");
		data->r_w = 1;
		data->size = count;
		rdata = count;
		return rdata;
	}
	else
	{
		printk("copy from user not done successfully\n");
		return -1;
	}
}
long ioctl_fn(struct file *filep, unsigned int cmd,unsigned long arg)
{
	arg = &data;
	return 0;
}

int release_fn(struct inode *inode, struct file *filep)
{
	printk("good bye from driver\n");
	return 0;
}
struct cdev *app1;
dev_t dr_dn;
static int dri_on(void)
{
	printk("welcome\n");
	int major, minor;
	int reg_res = alloc_chrdev_region(&dr_dn,0,1,"dri");
	if(reg_res <0)
	{
		printk("registration not possible\n");
		return -1;
	}
	major = MAJOR(dr_dn);
	minor = MINOR(dr_dn);

	printk("major: %d and minor: %d\n",major,minor);
	app1 = cdev_alloc();
	app1->ops = &op;
	int add_res = cdev_add(app1,dr_dn,1);
	if(add_res < 0)
	{
		printk("no success\n");
		return -1;
	}
	return 0;
}

static void dri_off(void)
{
	printk("logging off from driver\n");
	cdev_del(app1);
	printk("device log off\n");
	unregister_chrdev_region(dr_dn,1);
	printk("driver off\n");
}

module_init(dri_on);
module_exit(dri_off);

//MUDULE_LICENSE("GPL");
//MODULE_AUTHOR("ANURAG");
//MUDULE_DESCRIPTION("exam q 2");	
