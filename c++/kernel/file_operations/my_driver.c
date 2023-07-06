#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

static dev_t my_dev;
static char *dev_name = "my_driver";

struct my_device {
    struct cdev cdev;
};
static struct my_device my_dev_struct;

static int my_driver_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "my_driver: device opened\n");
    return 0;
}

static int my_driver_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "my_driver: device released\n");
    return 0;
}

static ssize_t my_driver_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    char *msg = "Hello, world!\n";
    int len = strlen(msg);
    if (count < len)
        return -EINVAL;
    if (*offset != 0)
        return 0;
    if (copy_to_user(buf, msg, len))
        return -EFAULT;
    *offset = len;
    return len;
}

static struct file_operations my_driver_fops = {
    .owner = THIS_MODULE,
    .open = my_driver_open,
    .release = my_driver_release,
    .read = my_driver_read,
};

static int __init my_driver_init(void)
{
    int ret;
    ret = alloc_chrdev_region(&my_dev, 0, 1, dev_name);
    if (ret < 0) {
        printk(KERN_ERR "my_driver: failed to allocate device number\n");
        return ret;
    }
    cdev_init(&my_dev_struct.cdev, &my_driver_fops);
    my_dev_struct.cdev.owner = THIS_MODULE;
    ret = cdev_add(&my_dev_struct.cdev, my_dev, 1);
    if (ret < 0) {
        printk(KERN_ERR "my_driver: failed to add device\n");
        unregister_chrdev_region(my_dev, 1);
        return ret;
    }
    printk(KERN_INFO "my_driver: module loaded\n");
    return 0;
}

static void __exit my_driver_exit(void)
{
    cdev_del(&my_dev_struct.cdev);
    unregister_chrdev_region(my_dev, 1);
    printk(KERN_INFO "my_driver: module unloaded\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

