/*******************************************************************************
* 文 件 名: char_framework.c
* 文件描述: linux驱动编写（字符设备编写框架）
* 备    注: 标准文件操作：支持 open、close、read、write、lseek 和 ioctl
* 作    者: HanKin
* 创建日期: 2025.07.15
* 修改日期：2025.07.15
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/version.h>
 
#include <asm/io.h>
#include <asm/switch_to.h>
#include <asm/uaccess.h>
 
#define CHRMEM_SIZE 0x1000
#define MEM_CLEAR   0x1
 
static int chr_major;
 
struct chr_dev
{
	struct cdev cdev;	// 内核用于管理字符设备的核心结构，包含操作函数指针
	unsigned char mem[CHRMEM_SIZE];	// 内存缓冲区：大小为 CHRMEM_SIZE（0x1000 字节），用于存储用户数据
};
 
struct chr_dev* char_devp;

// static的重要性warning: no previous prototype for ‘chr_open’ [-Wmissing-prototypes]
static int chr_open(struct inode* inode, struct file* filp)
{
	filp->private_data = char_devp;
	return 0;
}

// 设备关闭时调用，此处为空操作
static int chr_release(struct inode* inode, struct file* filp)
{
	return  0;
}

// 处理自定义命令（如 MEM_CLEAR 清空缓冲区）
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 0, 0)
// 旧内核使用 ioctl
static int chr_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#else
// 新内核使用 unlocked_ioctl
static long chr_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
#endif
{
	struct chr_dev* dev = filp->private_data;
	
	switch(cmd)
	{
		case MEM_CLEAR:
			memset(dev->mem, 0, CHRMEM_SIZE);
			break;
			
		default:
			return -EINVAL;
	}

	return 0;
}

// 将数据从内核缓冲区复制到用户空间（copy_to_user）
static ssize_t chr_read(struct file* filp, char __user* buf, size_t size, loff_t* ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct chr_dev* dev = filp->private_data;
	
	if(p >= CHRMEM_SIZE)
	{
		return 0;
	}
	
	if(count > CHRMEM_SIZE - p)
	{
		return 0;
	}

	// 从内核缓冲区复制数据到用户空间
	if(copy_to_user(buf, (void*)(dev->mem + p), count))
	{
		return -EINVAL;
	}
	else
	{
		*ppos += count;
		ret = count;
	}
	
	return ret;
}

// 将数据从用户空间复制到内核缓冲区（copy_from_user）
static ssize_t chr_write(struct file* filp, const char __user* buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct chr_dev* dev = filp->private_data;
	
	if(p >= CHRMEM_SIZE)
	{
		return 0;
	}
	
	if(count > CHRMEM_SIZE - p)
	{
		count = CHRMEM_SIZE - p;
	}

	// 从用户空间复制数据到内核缓冲区
	if(copy_from_user(dev->mem + p, buf, count))
	{
		ret = -EINVAL;
	}
	else
	{
		*ppos += count;
		ret = count;
	}
	
	return ret;
}

// 实现文件定位功能，支持 SEEK_SET、SEEK_CUR、SEEK_END
static loff_t chr_llseek(struct file* filp, loff_t offset, int orig)
{
	loff_t ret = 0;
	
	/* orig can be SEEK_SET, SEEK_CUR, SEEK_END */
	switch(orig)
	{
		case 0:
			if(offset < 0)
			{
				ret = -EINVAL;
				break;
			}
			
			if((unsigned int) offset > CHRMEM_SIZE)
			{
				ret = -EINVAL;
				break;
			}
			
			filp->f_pos = (unsigned int) offset;
			ret = filp->f_pos;
			break;
			
		case 1:
			if((filp->f_pos + offset) > CHRMEM_SIZE)
			{
				ret = -EINVAL;
				break;
			}
			
			if((filp->f_pos + offset) < 0)
			{
				ret = -EINVAL;
				break;
			}
			
			filp->f_pos += offset;
			ret = filp->f_pos;
			break;
			
		default:
			ret = - EINVAL;
			break;
	}
	
	return ret;
}

// 文件操作函数
static const struct file_operations chr_ops = 
{
	.owner    = THIS_MODULE,
	.llseek   = chr_llseek,
	.read     = chr_read,
	.write    = chr_write,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 0, 0)
    .ioctl    = chr_ioctl,
#else
    .unlocked_ioctl = chr_unlocked_ioctl,
#endif
	.open     = chr_open,
	.release  = chr_release
};

static void chr_setup_cdev(struct chr_dev* dev, int index)
{
	int err;
	int devno = MKDEV(chr_major, index);
	
	cdev_init(&dev->cdev, &chr_ops);
	dev->cdev.owner = THIS_MODULE;
	
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		printk(KERN_NOTICE "Error happend!\n");
	}
}

static int chr_init(void)
{
	int result;
	dev_t ndev;

	// 1. 动态分配设备号
	result = alloc_chrdev_region(&ndev, 0, 1, "chr_dev");  
    if(result < 0 ) {
        return result;
    } 	
	
	printk("chr_init(): major = %d, minor = %d\n", MAJOR(ndev), MINOR(ndev));
    chr_major = MAJOR(ndev);

	// 2.分配并初始化设备结构体
	char_devp = kmalloc(sizeof(struct chr_dev), GFP_KERNEL);
	if (!char_devp) {
		result = -ENOMEM;
		goto final;
	}
	memset(char_devp, 0, sizeof(struct chr_dev));

	// 3. 注册字符设备
	chr_setup_cdev(char_devp, 0);
	return 0;
	
final:
	unregister_chrdev_region(ndev, 1);
	return 0;
}

static void chr_exit(void)
{
	cdev_del(&char_devp->cdev);
	kfree(char_devp);
	unregister_chrdev_region(MKDEV(chr_major, 0), 1);
}
 
module_init(chr_init);
module_exit(chr_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("feixiaoxing!163.com");
MODULE_DESCRIPTION("A simple device example!");