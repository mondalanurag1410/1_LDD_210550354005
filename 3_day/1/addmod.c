#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include "head.h" // include own hearder file

static int my_add(int,int); // declaration of function

static int my_add(int a,int b) // add funtion
{
	return (a+b);
}
EXPORT_SYMBOL_GPL(my_add); // export the add function as shared object

static int my_init(void) // initialze module
{
	printk("welcome to addition program module\n");
	return 0;
}

static void my_clean(void) // exit module finction
{
	printk("bye from add\n");
}

module_init(my_init);
module_exit(my_clean);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("add function declaration");
