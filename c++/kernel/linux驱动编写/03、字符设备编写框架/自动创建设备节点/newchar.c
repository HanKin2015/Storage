/*******************************************************************************
* 文 件 名: newchar.c
* 文件描述: 自动创建设备节点，modprobe/insmod ./newchar.ko
* 备    注: /dev/NEWCHAR  /sys/class/led_class  cat /proc/devices -->> 240 NEWCHAR
* 作    者: HanKin
* 创建日期: 2025.07.16
* 修改日期：2025.07.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include <linux/version.h>

#define NEWCHR_CNT 1
#define NEWCHR_NAME "NEWCHR"      // 设备名称
#define CLASS_NAME  "led_class"   // 类名称

//内核缓存区
static char readbuf[100];						//读数据缓存
static char writebuf[100];						//写数据缓存
static char kerneldata[] = {"kernel data!"};	//测试数据
//硬件寄存器
#define GPIO_TEST_BASE (0x01234567) 	//宏定义寄存器映射地址
static void __iomem *GPIO_TEST;			// __iomem 类型的指针，指向映射后的虚拟空间首地址

/* newchr设备结构体 */
struct newchr_dev {
	dev_t devid;			/* 设备号   */
	struct cdev cdev;		/* cdev     */
	struct class *class;	/* 类       */
	struct device *device;	/* 设备实例 */
	int major;				/* 主设备号 */
	int minor;				/* 次设备号 */
};
 
struct newchr_dev newchr;	/* newchr设备 */

//打开设备
static int chrdevbase_open(struct inode *inode, struct file *filp) 
{
	filp->private_data = &newchr; /* 设置私有数据 */
	return 0;
}
// 从设备读取数据 
static ssize_t chrdevbase_read(struct file *filp , char __user *buf , size_t cnt , loff_t *offt) 
{
	int retvalue = 0;
	unsigned char databuf[1];
	//读取私有数据
	struct newchr_dev *dev = (struct newchr_dev *)filp->private_data;
// 读取硬件寄存器
#if 0  
	//读取寄存器状态
	databuf[0] = readl(GPIO_TEST);
	retvalue = copy_to_user(buf , databuf, cnt);
//读取内核内存
#else	
	//测试数据拷贝到读数据缓存中
    memcpy(readbuf , kerneldata , sizeof(kerneldata));  
    //内核中数据（读缓存）拷贝到用户空间
    retvalue = copy_to_user(buf , readbuf , cnt);
#endif

    if(retvalue == 0) printk("kernel senddate ok!\n");   
  	else printk("kernel senddate failed!\n");
    return 0;
}
//向设备写数据 
static ssize_t chrdevbase_write(struct file *filp, const char __user *buf, size_t cnt , loff_t *offt) 
{
	int retvalue = 0;
	//读取私有数据
	struct newchr_dev *dev = (struct newchr_dev *)filp->private_data;
//写硬件寄存器
#if 0
	writel(buf[0],GPIO_TEST);
//写内核缓存
#else
	//用户数据拷贝到内核空间（写缓存）
    retvalue = copy_from_user(writebuf , buf ,cnt);
#endif
    if(retvalue == 0) printk("kernel recevdate : %s\n",writebuf);
  	else printk("kernel recevdate failed!");
    return 0;
}
//关闭/释放设备
static int chrdevbase_release(struct inode *inode , struct file *filp) 
{
	return 0;
}
//设备操作函数
static struct file_operations chrdevbase_fops = {
    .owner = THIS_MODULE,
    .open = chrdevbase_open,
    .read = chrdevbase_read,
    .write = chrdevbase_write,
    .release = chrdevbase_release,
};
/* 驱动入口函数 */
static int __init chrdevbase_init(void)
{
	//寄存器物理映射，物理地址映射到虚拟地址指针
	GPIO_TEST= ioremap(GPIO_TEST_BASE, 4);
	
	//申请设备号
    if(newchr.major)		//静态申请
    {
        newchr.devid = MKDEV(newchr.major , 0);
        register_chrdev_region(newchr.devid, NEWCHR_CNT,NEWCHR_NAME);
    }else					//动态申请
    {
        alloc_chrdev_region(&newchr.devid , 0 , NEWCHR_CNT , NEWCHR_NAME);
        newchr.major = MAJOR(newchr.devid);
        newchr.minor = MINOR(newchr.devid);
    }   
    printk("newche major=%d,minor=%d\r\n",newchr.major , newchr.minor);

	//字符串设备初始化、注册添加到内核
	newchr.cdev.owner = THIS_MODULE;
    cdev_init(&newchr.cdev , &chrdevbase_fops);
    cdev_add(&newchr.cdev , newchr.devid ,NEWCHR_CNT);
	//创建设备类
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0)
    newchr.class = class_create(CLASS_NAME);
#else
    newchr.class = class_create(THIS_MODULE, CLASS_NAME);
#endif
    if(IS_ERR(newchr.class))
    {
        return PTR_ERR(newchr.class);
    }
	//创建类的实例化设备 ,dev下面创建文件
    newchr.device = device_create(newchr.class , NULL , newchr.devid ,NULL ,NEWCHR_NAME);
    if(IS_ERR(newchr.device))
    {
        return PTR_ERR(newchr.device);
    }
    return 0;
}
/* 驱动出口函数 */
static void __exit chrdevbase_exit(void)
{
	//解除寄存器映射
	iounmap(GPIO_TEST);
	//删除cdev字符串设备
	cdev_del(&newchr.cdev);
	//释放设备号
    unregister_chrdev_region(newchr.devid , NEWCHR_CNT);
	//具体设备注销
    device_destroy(newchr.class, newchr.devid);
    //类注销
    class_destroy(newchr.class);
}
/* 将上面两个函数指定为驱动的入口和出口函数 */
module_init(chrdevbase_init);
module_exit(chrdevbase_exit);

// 这个许可证写错会编译报错RROR: modpost: GPL-incompatible module newchar.ko uses GPL-only symbol 'class_create'
MODULE_LICENSE("GPL");  // 明确声明采用GPL许可证
// 或使用更宽松的GPL兼容版本
//MODULE_LICENSE("GPL v2");

MODULE_AUTHOR("songwei");//作者信息
