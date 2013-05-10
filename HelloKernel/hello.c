#include <linux/module.h>
#include <linux/init.h>

/**
 * The init function is called when the module is loaded.
 */
static int hello_init(void)
{
	printk(KERN_INFO "Hello Linux Kernel Modules World!\n");

	return 0;
}

/**
 * The exit function is called when the module is removed.
 */
static void hello_exit(void)
{
	printk(KERN_INFO "See you around Linux Kernel Modules World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Long Luo");
MODULE_DESCRIPTION("Hello World Kernel module");
