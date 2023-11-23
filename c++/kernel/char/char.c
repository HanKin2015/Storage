/*******************************************************************************
* 文 件 名: char.c
* 文件描述: linux驱动编写（入门）
* 备    注: https://blog.csdn.net/feixiaoxing/article/details/8537738
* 作    者: HanKin
* 创建日期: 2023.11.22
* 修改日期：2023.11.22
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
 
static struct cdev chr_dev;
static dev_t ndev;
 
static int chr_open(struct inode* nd, struct file* filp)
{
	int major ;
	int minor;
	
	major = MAJOR(nd->i_rdev);
	minor = MINOR(nd->i_rdev);
	
	printk("chr_open, major = %d, minor = %d\n", major, minor);
	return 0;
}
 
static ssize_t chr_read(struct file* filp, char __user* u, size_t sz, loff_t* off)
{
	printk("chr_read process!\n");
	return 0;
}
 
struct file_operations chr_ops = {
	.owner = THIS_MODULE,
	.open = chr_open,
	.read = chr_read
};
 
static int demo_init(void)
{
	int ret;
	
	cdev_init(&chr_dev, &chr_ops);
	ret = alloc_chrdev_region(&ndev, 0, 1, "chr_dev");
	if(ret < 0 )
	{
		return ret;
	}
	
	printk("demo_init(): major = %d, minor = %d\n", MAJOR(ndev), MINOR(ndev));
	ret = cdev_add(&chr_dev, ndev, 1);
	if(ret < 0)
	{
		return ret;
	}
	
	return 0;
}
 
static void demo_exit(void)
{
	printk("demo_exit process!\n");
	cdev_del(&chr_dev);
	unregister_chrdev_region(ndev, 1);
}
 
module_init(demo_init);
module_exit(demo_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("feixiaoxing@163.com");
MODULE_DESCRIPTION("A simple device example!");