#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define mem_size        1           //Memory Size

dev_t dev = 0;
static struct cdev etx_cdev;
char asteriskBuf = '*';
char dotBuf = '.';
void *pVoid;
int counter = 0;

/*
** Function Prototipes
*/
static int      __init init_function(void);
static void     __exit exit_function(void);
static ssize_t  driver_read(struct file *flip, char __user *buf, size_t len, loff_t * off);


static struct file_operations fops = 
{
    .owner      = THIS_MODULE,
    .read       = driver_read,
};


/**
 * This function will be called when we read the Device file
 */
static ssize_t driver_read(struct file *flip, char __user *buf, size_t len, loff_t * off)
{
    counter++;
    if (counter % 10 == 0)
    {
        pVoid = &asteriskBuf;
    } else {
        pVoid = &dotBuf;
    }
    //Copy the data from the kernel space to the user-space
    if(copy_to_user(buf, pVoid, mem_size))
    {
        pr_err("Data Read : Err!\n");
    }

    return mem_size;
}

static int __init init_function(void)
{
    /*Allocating Major Number*/
    if ((alloc_chrdev_region(&dev, 0, 1, "dots")) < 0)
    {
        pr_err("Cannot allocate major number for device\n");
        return -1;
    }

    pr_info("Major = %d, Minor = %d \n", MAJOR(dev), MINOR(dev));

    /* Creating cdev structure*/
    cdev_init(&etx_cdev, &fops);

    /* Adding character device to the system */
    if((cdev_add(&etx_cdev, dev, 1)) < 0)
    {
        pr_err("Cannot add the device to the system");
        goto r_class;
    }

    pr_info("Kernel Module Inserted Succeddfully...\n");
    return 0;

r_class:
    unregister_chrdev_region(dev, 1);
    return -1;
}

/*
** Module exit function
*/
static void __exit exit_function(void)
{
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev, 1);
    pr_info("Kernel Module Removed Successfully...\n");
}

module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Facundo Ramallo");
MODULE_DESCRIPTION("Simple Character Device Driver (Manually Creating a Device File)");
MODULE_VERSION("1.1");