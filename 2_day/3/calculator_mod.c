#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h> // header file for module parameter operation
#include <linux/string.h> // header file for string operation

/*initilization of variables*/
static char* op= "hi"; 
static int num1 = 0;
static int num2 = 0;

/*take module parameter commmand line arguments*/
module_param(op, charp, S_IRUSR | S_IWUSR);
module_param(num1, int, S_IRUSR | S_IWUSR);
module_param(num2, int, S_IRUSR | S_IWUSR);


static int cal_mod_in(void) // module initialization function
{
	printk("welcome to cal culator module\n");
	int result; // initialized result variable
	if(strcmp(op,"add") == 0) // comparing sting with the string given in command line as argument
	{	
		/*funtion for addition*/
		result = num1 + num2;
		printk("the addition result of %d and %d is: %d\n",num1,num2,result);
	}
	else if(strcmp(op,"sub") == 0)  // comparing string with comman line argument
	{
		result = num1 - num2;
		printk("the substraction result of %d and %d is: %d\n",num1,num2,result);
	}
	else if(strcmp(op,"mul") == 0) // comparison of string
	{
		result = num1 * num2;
		printk("the multiplication of %d and %d is: %d\n",num1,num2,result);
	}
	else if(strcmp(op,"div") == 0) // comparision of string
	{
		result = num1 / num2;
		printk("the division of %d and %d is: %d\n",num1,num2,result);
	}
	
	return 0;
}


static void cal_mod_ex(void) // module exit function
{
	printk("closing calculator module\n");
}

module_init(cal_mod_in);
module_exit(cal_mod_ex);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANURAG");
MODULE_DESCRIPTION("day2: q3: calcultor LKM");
