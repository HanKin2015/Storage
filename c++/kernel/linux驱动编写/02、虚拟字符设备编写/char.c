/*******************************************************************************
* 文 件 名: char.c
* 文件描述: linux驱动编写（入门）
* 备    注: https://blog.csdn.net/feixiaoxing/article/details/8537738
* 作    者: HanKin
* 创建日期: 2023.11.22
* 修改日期：2025.07.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

// 字符设备核心结构体，用于描述字符设备的属性和操作函数
static struct cdev chr_dev;

// 设备号类型，包含主设备号（标识设备类型）和次设备号（标识具体设备实例）
static dev_t ndev;

/*
功能：当用户空间通过 open() 系统调用打开设备文件时触发。
参数：
inode：包含设备的静态信息（如设备号）。
file：表示打开的文件实例（如文件标志、偏移量）。
作用：打印设备的主、次设备号，返回 0 表示成功。
*/
static int chr_open(struct inode* nd, struct file* filp)
{
	int major;
	int minor;
	
	major = MAJOR(nd->i_rdev);
	minor = MINOR(nd->i_rdev);
	
	printk("chr_open, major = %d, minor = %d\n", major, minor);
	return 0;
}

/*
功能：当用户空间通过 read() 系统调用读取设备时触发。
参数：
filp：文件指针。
u：用户空间缓冲区地址（__user 标记表示该指针来自用户空间）。
sz：请求读取的字节数。
off：文件偏移量。
作用：仅打印日志，返回 0 表示未读取任何数据。
*/
static ssize_t chr_read(struct file* filp, char __user* u, size_t sz, loff_t* off)
{
	printk("chr_read process!\n");
	printk("sz = %lu\n", sz);
	return 123; // 表示读到123字节数据
}

/*
功能：定义设备支持的操作函数，是连接内核与驱动的桥梁。
关键字段：
owner：指向当前模块，避免在使用时被卸载。
open：对应 chr_open 函数，处理设备打开操作。
read：对应 chr_read 函数，处理设备读取操作。
*/
struct file_operations chr_ops = {
	.owner = THIS_MODULE,
	.open = chr_open,
	.read = chr_read
};

// 模块加载时自动调用，完成设备初始化和注册
static int demo_init(void)
{
	int ret;
	
    // 初始化字符设备结构体
	cdev_init(&chr_dev, &chr_ops);

    // 动态分配设备号（主设备号由内核分配，次设备号从 0 开始，数量 1）
	ret = alloc_chrdev_region(&ndev, 0, 1, "chr_dev");
	if(ret < 0 )
	{
		return ret;
	}
	
	printk("demo_init(): major = %d, minor = %d\n", MAJOR(ndev), MINOR(ndev));

    // 注册字符设备到内核
	ret = cdev_add(&chr_dev, ndev, 1);
	if(ret < 0)
	{
		return ret;
	}
	
	return 0;
}

// 模块卸载时自动调用，释放资源
static void demo_exit(void)
{
	printk("demo_exit process!\n");
	cdev_del(&chr_dev);
	unregister_chrdev_region(ndev, 1);
}
 
module_init(demo_init);
module_exit(demo_exit);

// 声明模块的许可证、作者和描述信息
MODULE_LICENSE("GPL");
MODULE_AUTHOR("feixiaoxing@163.com");
MODULE_DESCRIPTION("A simple device example!");