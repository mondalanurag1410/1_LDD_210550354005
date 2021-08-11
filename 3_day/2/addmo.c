#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include "head.h"

static int add_mo(int,int);

static int add_mo(int a,int b)
{
	return (a+b);
}
EXPORT_SYMBOL_GPL(add_mo);

static int mod_init(void)
{
	printk("welcome to addition module\n");
	return 0;
}

static void mod_clean(void)
{
	printk("bye add\n");
}

module_init(mod_init);
module_exit(mod_clean);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("add linux kernel module");
