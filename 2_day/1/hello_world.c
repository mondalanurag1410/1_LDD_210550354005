/*Write the Hello World Module Program. Write the Makefile to compile the Module Program. 
 * Compile and load the Module into the Kernel*/

#include <linux/init.h> // header file for modules
#include <linux/module.h>

static int mymodule_init(void) // module initialization function
{
	printk("welcome to the hello world module\n");
	return 0; // always return 0 to tell the all the resources user asked for kernel provided those completely
}

static void mymodule_exit(void) // module exit function no return value
{
	printk("good bye from module\n");
}

module_init(mymodule_init); // macro for initialization
module_exit(mymodule_exit); // macro for exit 

MODULE_LICENSE("GPL"); // macro for GPL
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("Day 1: Question 1");
