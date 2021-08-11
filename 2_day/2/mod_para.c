#include <linux/module.h>
#include <linux/moduleparam.h> // header file for module parameter
#include <linux/init.h>

static int value = 10; // initialize variable

module_param(value,int,S_IRUSR | S_IWUSR); // taking variable as command line argument

static int my_mod_para_init(void) // initialize module function
{
	printk("welcome to my module.\n");
	printk("the value in module parameter: %d\n",value); // printing of command line argument
	return 0;
}

static void my_mod_para_exit(void) // exit module function
{
	printk("good bye\n");
}

module_init(my_mod_para_init);
module_exit(my_mod_para_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("day2: q2: parameter input linux kernel module");
