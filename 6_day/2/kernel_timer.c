#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>

static struct timer_lisit my_timer; // create one structure object
dev_t ktm_dn;
static int count=0;

static void tim_call_bck(struct timer_list *timer) // timer call back function
{
	printk("The timer callback function will called [%d]\n",count++);
	mod_timer(&my_timer,jiffies + msecs_to_jiffies(2000)); // for repeate the same thing with two second interval
							       //amount of time is always taken in jiffies
}

struct cdev *MyTimerDevice;
static int tim_on(void)
{
	int minor, major;
	int reg_res;
	ktm_dn = MKDEV(255,0); // make device number statically
	minor = MINOR(ktm_dn); // finding minor no
	major = MAJOR(ktm_dn); // finding major no

	reg_res = register_chrdev_region(ktm_dn,1,"ktm_driver"); // register character driver in the kernel
	if(reg_res < 0) // condition whether registration done properly or not
	{
		printk("driver region allocation not done\n");
		return -1;
	}
	printk("kernel timer region registration done\nwith major no: %d and minor no: %d\n",major,minor);
	timer_setup(&my_timer,tim_call_bck,0); // setup the timer with call back function 
	int ret = mod_timer(&my_timer,jiffies + msecs_to_jiffies(2000)); // modify the timing interval
	if(ret == 0) // condition whether after timing interval it fiers or not
	{
		printk("Not able to fire\n");
	}
	return 0;
}

static void tim_off(void)
{
	printk("driver going to log off\n");
	del_timer(&my_timer); // deletion of the timer
	printk("good bye\n");
}

module_init(tim_on);
module_exit(tim_off);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("timer module LKM");
	
