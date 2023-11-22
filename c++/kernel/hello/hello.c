/*******************************************************************************
* 文 件 名: hello.c
* 文件描述: linux驱动编写（入门）
* 备    注: https://blog.csdn.net/feixiaoxing/article/details/8533822
* 作    者: HanKin
* 创建日期: 2023.11.22
* 修改日期：2023.11.22
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/module.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("feixiaoxing");
MODULE_DESCRIPTION("This is just a hello module!\n");
 
static int __init hello_init(void)
{
        printk(KERN_EMERG "hello, init\n");
        return 0;
}
 
static void __exit hello_exit(void)
{
        printk(KERN_EMERG "hello, exit\n");
}
 
module_init(hello_init);
module_exit(hello_exit);