#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include "head.h"

static int a = 10;
static int b =20;

static int avg_init(void)
{
	int avg;
	printk("welcome to average module\n");
	avg = add_mo(a,b)/2;
	printk("the average of %d and %d is %d",a,b,avg);
	return 0;
}

static void avg_clean(void)
{
	printk("bye avg module\n");
}

module_init(avg_init);
module_exit(avg_clean);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("average linus kernel module");
