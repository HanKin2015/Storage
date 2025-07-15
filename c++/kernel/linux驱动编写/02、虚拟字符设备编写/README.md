region地区，区域；行政区

在module_init中的函数是模块加载时处理的函数
而模块卸载的函数则是在module_exit中
每一个设备都要对应一个基本的设备数据，当然为了使得这个设备注册在整个系统当中，
还需要分配一个设备节点，alloc_chrdev_region就完成这样一个功能。
等到cdev_add的时候，整个设备注册的过程就全部完成了，就是这么简单。

## 运行结果
insmod安装驱动后，在dmesg中打印了demo_init(): major = 240, minor = 0，可以看到设备为我们创建的major、minor数值是多少。

然后利用它们直接创建设备节点了，输入mknod /dev/chr_dev c 240 0即可
注意：这个命令怎么都是正常的，因此需要写入正确的major和minor才行。

## 主设备号（Major Number） 和 次设备号（Minor Number）
在 Linux 系统中，主设备号（Major Number） 和 次设备号（Minor Number） 是内核用于识别和管理硬件设备的关键标识符。它们是设备节点（位于 /dev 目录下）的核心属性，用于将用户空间的 I/O 请求路由到正确的驱动程序和设备实例。

1. 设备节点（Device Node）
是 /dev 目录下的特殊文件，用于表示硬件设备（如硬盘、串口、键盘）。
通过 mknod 命令创建，或由 udev 动态生成。

2. 主设备号（Major Number）
作用：标识设备类型，映射到对应的驱动程序。
范围：0-4095（2^12），但实际使用中通常小于 256。
示例：
主设备号 1 对应内存设备（如 /dev/mem）。
主设备号 8 对应 SCSI/SATA 硬盘（如 /dev/sda）。

3. 次设备号（Minor Number）
作用：标识同一驱动管理的不同设备实例。
范围：0-1048575（2^20）。
示例：
/dev/sda（次设备号 0）表示第一块 SCSI 硬盘。
/dev/sdb（次设备号 16）表示第二块 SCSI 硬盘。

二、数据结构与存储方式
1. dev_t 类型
是 unsigned int 类型，用于存储设备号（主设备号 + 次设备号）。
内核通过宏操作分离和组合主 / 次设备号：
```
MAJOR(dev_t dev);  // 提取主设备号
MINOR(dev_t dev);  // 提取次设备号
MKDEV(int major, int minor);  // 组合成 dev_t
```

现代 Linux 系统通过 udev 自动创建设备节点，规则文件通常位于 /etc/udev/rules.d/：
```
# 示例：为自定义设备设置固定名称
KERNEL=="ttyUSB*", ATTRS{idVendor}=="1234", ATTRS{idProduct}=="5678", NAME="my_usb_device"
```



