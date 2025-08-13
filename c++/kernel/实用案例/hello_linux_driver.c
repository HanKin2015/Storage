/*******************************************************************************
* 文 件 名: hello_linux_driver.c
* 文件描述: linux驱动编写（入门）
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.12
* 修改日期：2025.08.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <linux/module.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("HanKin");
MODULE_DESCRIPTION("This is just a hello module!\n");
 
static int __init hello_init(void)
{
    printk(KERN_INFO "hello, init\n");
    return 0;
}
 
static void __exit hello_exit(void)
{
    printk(KERN_EMERG "hello, exit\n");
}
 
module_init(hello_init);
module_exit(hello_exit);