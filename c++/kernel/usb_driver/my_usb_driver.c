/**
* 文 件 名: calc_asap_value.cpp
* 文件描述: 计算asap值，之前排查问题怀疑是这个值异常导致的问题，实际上不是
* 作    者: HanKin
* 创建日期: 2023.05.05
* 修改日期：2023.05.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <linux/module.h>
#include <linux/usb.h>

static struct usb_device_id my_usb_table[] = {
    { USB_DEVICE(0x1234, 0x5678) },
    { } /* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, my_usb_table);

static struct usb_driver my_usb_driver = {
    .name = "my_usb_driver",
    .id_table = my_usb_table,
    .probe = my_usb_probe,
    .disconnect = my_usb_disconnect,
};

static int my_usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    /* 设备连接时的处理逻辑 */
    return 0;
}

static void my_usb_disconnect(struct usb_interface *interface)
{
    /* 设备断开时的处理逻辑 */
}

static int __init my_usb_init(void)
{
    int ret = usb_register(&my_usb_driver);
    if (ret)
        printk(KERN_ERR "Failed to register USB driver\n");
    return ret;
}

static void __exit my_usb_exit(void)
{
    usb_deregister(&my_usb_driver);
}

module_init(my_usb_init);
module_exit(my_usb_exit);

