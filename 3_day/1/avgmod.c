/*Write a module program Add.c that exports the add functionality using the EXPORT_SYMBOL macro. 
 * Write another module program Average.c that calls the add function, 
 * exported by the Add Module and computes the average of 2 numbers. 
 * Manually implement and demonstrate this functionality.*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include "head.h"

/*define two variables*/
static int a = 20;
static int b = 10;

static int avg_init(void) // module function initialization
{
	int avg;
	printk("welcome to average\n");
	avg = my_add(a,b)/2; // calling the shared add function 
	printk("the average of %d and %d is %d\n",a,b,avg);
	return 0;
}

static void avg_exit(void) // module exit function
{
	printk("bye from avg\n");
}

module_init(avg_init);
module_exit(avg_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("simple average module");
