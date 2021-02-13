#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

static int __init hello_world_init(void)
{
	printk(KERN_INFO "Hello World!\n");

	return 0;
}

void __exit hello_world_exit(void)
{
	printk(KERN_INFO "Good Bye, Cruel World!\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Facundo J. Ramallo");
MODULE_DESCRIPTION("Driver1.0 - A simple hello world driver");
MODULE_VERSION("1:1.0");