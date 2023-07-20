# USB设备驱动卸载

## 1、文件说明
- Andriod8.1目录是在安卓系统上面编译，与remount_kernel_driver.c类似
- remount_kernel_driver.c 最开始接触这个编写的，暴力的将libusb实现的封装函数迁移出来，直接使用ioctl函数
- replace_kernel_driver.c 使用libusb库封装函数学习各个函数的使用
- redir_udev_mount_usbfs_driver.c 最终的目的实现，这才发现usbfs驱动其实是使用usbfs接口加载的自家驱动
- if_error_instruct_example.c 额外发现的新知识

测试发现如果只是卸载驱动是无法加载usbfs驱动的，还需要请求访问权限，即claim interface。

## 2、命令操作
lsmod
rmmod

## 3、编译报错大量的未定义
编译发现代码中是使用r = ioctl(fd, IOCTL_USBFS_IOCTL, &command);，编译却发现IOCTL_USBFS_IOCTL未定义，发现原函数定义在libusb-1.0.24/libusb/os/linux_usbfs.h这里。
```
#define IOCTL_USBFS_CLAIMINTERFACE  _IOR('U', 15, unsigned int)
#define IOCTL_USBFS_RELEASEINTERFACE    _IOR('U', 16, unsigned int)
#define IOCTL_USBFS_CONNECTINFO     _IOW('U', 17, struct usbfs_connectinfo)
#define IOCTL_USBFS_IOCTL       _IOWR('U', 18, struct usbfs_ioctl)
#define IOCTL_USBFS_RESET       _IO('U', 20)
#define IOCTL_USBFS_CLEAR_HALT      _IOR('U', 21, unsigned int)
#define IOCTL_USBFS_DISCONNECT      _IO('U', 22)
#define IOCTL_USBFS_CONNECT     _IO('U', 23)
```

我是将libusb-1.0.24/libusb/os/linux_usbfs.c文件的op_attach_kernel_driver函数直接复制粘贴过来的，然后在linux内核文件linux-5.15.4/include/uapi/linux/usbdevice_fs.h找到相关定义。
```
#define USBDEVFS_CLAIMINTERFACE    _IOR('U', 15, unsigned int)
#define USBDEVFS_RELEASEINTERFACE  _IOR('U', 16, unsigned int)
#define USBDEVFS_CONNECTINFO       _IOW('U', 17, struct usbdevfs_connectinfo)
#define USBDEVFS_IOCTL             _IOWR('U', 18, struct usbdevfs_ioctl)
#define USBDEVFS_IOCTL32           _IOWR('U', 18, struct usbdevfs_ioctl32)
#define USBDEVFS_HUB_PORTINFO      _IOR('U', 19, struct usbdevfs_hub_portinfo)
#define USBDEVFS_RESET             _IO('U', 20)
#define USBDEVFS_CLEAR_HALT        _IOR('U', 21, unsigned int)
#define USBDEVFS_DISCONNECT        _IO('U', 22)
#define USBDEVFS_CONNECT           _IO('U', 23)
```

如将IOCTL_USBFS_IOCTL改成USBDEVFS_IOCTL，即r = ioctl(fd, USBDEVFS_IOCTL, &command);。

## 4、真相大白
我之前已经使用了libusb库获取handle和USB设备文件描述符等，迁移的函数本来就属于里面，我是可以直接调用的。。。。。

但有一点想不通，我编译已经指定libusb库了，就应该不会出现大量未定义问题，先试着看是否能直接调用此函数。

## 5、问题现象
在安卓4.2系统上面插入ZFM889触摸屏无响应，getevent无事件，但是发现cat /sys/kernel/debug/hid/0003\:AAEC\:C021.0010/events存在数据。

发现设备替换驱动为usbfs后再替换为usbhid驱动也能正常。

最终解决方案是：https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/commit/drivers/hid/hid-multitouch.c?h=v4.19.282&id=b897f6db3ae2cd9a42377f8b1865450f34ceff0e

## 6、Windows 8 devices
Windows 8 devices是指安装了Windows 8操作系统的设备，包括台式机、笔记本电脑、平板电脑、智能手机等。Windows 8是微软公司推出的一款操作系统，于2012年正式发布。相比于之前的Windows操作系统，Windows 8在界面设计、应用程序生态、安全性等方面都有较大的改进和优化，支持触摸屏操作和多种设备的无缝连接。因此，Windows 8 devices可以提供更加流畅、便捷、安全的用户体验。

## 7、如何确认一个设备是不是Windows 8 devices
在USB-IF官网上查询该设备的厂商ID和产品ID是否被认证为符合Windows 8设备兼容性要求的设备。如果该设备的厂商ID和产品ID被认证为符合Windows 8设备兼容性要求的设备，那么该USB设备就是Windows 8 devices。

USB设备的描述符中并没有特定的字段来表示Windows 8 devices。USB设备的描述符是由设备制造商定义的，用于描述设备的各种属性和功能，包括设备的厂商ID、产品ID、设备类别、设备协议等信息。Windows 8 devices是指安装了Windows 8操作系统的设备，而不是USB设备本身的属性或特征。

在Windows 8操作系统中，系统会根据USB设备的描述符信息来识别设备并加载相应的驱动程序。如果USB设备的描述符信息与Windows 8设备兼容性要求不符，那么可能会出现设备无法正常工作的问题。因此，在使用USB设备时，需要确认设备是否与Windows 8兼容，并安装相应的驱动程序。

Windows 8 devices并不仅仅指的是符合Windows 8规范的USB设备，而是指安装了Windows 8操作系统的设备，包括台式机、笔记本电脑、平板电脑、智能手机等。Windows 8是微软公司推出的一款操作系统，于2012年正式发布，相比于之前的Windows操作系统，在界面设计、应用程序生态、安全性等方面都有较大的改进和优化，支持触摸屏操作和多种设备的无缝连接。因此，Windows 8 devices可以提供更加流畅、便捷、安全的用户体验。

虽然Windows 8操作系统支持各种USB设备的连接和使用，但并不是所有的USB设备都能够在Windows 8上正常工作，一些老旧的USB设备可能需要安装特定的驱动程序才能在Windows 8上使用。如果您遇到了USB设备无法正常工作的问题，可以尝试更新驱动程序或者联系设备制造商获取支持。

概念很笼统，因为虽然这个commit提交提及到了这个Windows 8 devices，但是我不认为这个触摸屏是一个安装了Windows 8操作系统的设备，或许是保留了初识的quirk值解决了问题。

## 8、在USB-IF官网上查询该设备的厂商ID和产品ID是否被认证为符合Windows 8设备兼容性要求的设备
点击Products-》here结果需要注册账号登录，但是没有公司邮箱因此注册不了。

注册USB-IF官网账号出现The domain name of your email address does not match the accepted domains of your company.
这个错误提示意味着您使用的电子邮件地址的域名与您所在公司的域名不匹配。USB-IF官网要求注册用户的电子邮件地址必须与其所在公司的域名相匹配，这是为了确保注册用户的身份和公司信息的真实性和准确性。

如果您使用的电子邮件地址是您个人的邮件地址，而不是您所在公司的邮件地址，那么您需要使用您所在公司的邮件地址进行注册。如果您没有公司邮件地址，您可以联系USB-IF官网的客服人员，了解其他注册方式或解决方案。

另外，如果您已经使用了正确的公司邮件地址进行注册，但仍然出现了这个错误提示，那么您可以联系USB-IF官网的客服人员，寻求帮助和解决方案。

https://www.usbzh.com/article/detail-950.html

## 9、屏幕出现”Power Button Locked"
屏幕显示解除锁定：再次按住[1]和向上箭头↑10秒钟。

屏幕显示锁定：按住[1]和向上箭头↑10秒钟。这时按任意键，将显示osd locked(屏幕显示已锁定)5秒钟。

电源按钮锁定：按住[1]和向下箭头↓10秒钟。如果按下电源按钮，将显示power button locked(电源按钮已锁定)5秒钟。

在电源出现故障时，无论使用或不使用此设置，在电源恢复时viewpanel显示器的电源将自动接通。 电源按钮解除锁定：再次按住[1]和向下箭头↓10秒钟。

HP显示器电源键解锁方法： 开机情况下长按电源键解锁（10s 以上），直至显示器显示解锁提示。如果需再次锁定，再次长按即可锁定。

## 10、libusb库中op_claim_interface函数
libusb是一个用户空间的USB驱动库，op_claim_interface函数用于请求操作系统打开一个USB接口的访问权限，以便进行数据传输和控制传输。在使用libusb库进行USB通信时，需要先调用op_claim_interface函数请求打开USB接口的访问权限，然后才能进行数据传输和控制传输。如果请求成功，该函数将返回0，否则返回一个负数错误码。

打开USB接口的访问权限需要进行以下操作：
- 初始化libusb库：调用libusb_init函数初始化libusb库，以便后续使用libusb库进行USB通信。
- 打开USB设备：调用libusb_open函数打开需要进行USB通信的USB设备，获取一个libusb_device_handle句柄。
- 选择USB接口：调用libusb_set_configuration函数设置USB设备的配置，然后调用libusb_claim_interface函数请求打开需要进行USB通信的USB接口。
- 进行USB通信：如果请求打开USB接口的访问权限成功，就可以使用libusb_bulk_transfer函数进行数据传输和控制传输。
- 关闭USB接口和设备：使用libusb_release_interface函数释放USB接口的访问权限，然后调用libusb_close函数关闭USB设备。
- 退出libusb库：使用libusb_exit函数退出libusb库，释放资源。

## 11、claim interface为何需要卸载驱动
在Windows操作系统中，当一个USB设备被插入计算机时，操作系统会自动加载相应的驱动程序。如果该驱动程序与libusb库中的驱动程序冲突，就会导致无法打开USB接口的访问权限。因此，在使用libusb库进行USB通信时，需要先卸载操作系统自动加载的驱动程序，以便使用libusb库中的驱动程序。

具体来说，当调用libusb_claim_interface函数请求打开USB接口的访问权限时，libusb库会尝试卸载操作系统自动加载的驱动程序，并加载自己的驱动程序。如果卸载驱动程序失败，libusb_claim_interface函数将返回一个负数错误码。因此，在使用libusb库进行USB通信时，需要确保操作系统自动加载的驱动程序与libusb库中的驱动程序不冲突，或者手动卸载操作系统自动加载的驱动程序。

claim interface可以翻译成“请求接口访问权限”的意思。在libusb库中，claim interface指的是请求操作系统打开一个USB接口的访问权限，以便进行数据传输和控制传输。

## 12、理解libusb库
在libusb/os/linux_usbfs.c 文件中定义了op_claim_interface函数，但是直接调用是无法进行调用的，是内核层函数。
但是其中提供了用户空间接口：
```
const struct usbi_os_backend linux_usbfs_backend = {
.claim_interface = op_claim_interface,
};
```

然后在libusb/core.c 文件中使用指针引用：
```
#if defined(OS_LINUX)
const struct usbi_os_backend * const usbi_backend = &linux_usbfs_backend;
#elif defined(OS_DARWIN)
const struct usbi_os_backend * const usbi_backend = &darwin_backend;
#elif defined(OS_OPENBSD)
const struct usbi_os_backend * const usbi_backend = &openbsd_backend;
#elif defined(OS_NETBSD)
const struct usbi_os_backend * const usbi_backend = &netbsd_backend;
#elif defined(OS_WINDOWS)
const struct usbi_os_backend * const usbi_backend = &windows_backend;
#elif defined(OS_WINCE)
const struct usbi_os_backend * const usbi_backend = &wince_backend;
#else
#error "Unsupported OS"
#endif
```

## 13、#error的使用
C语言中有#error指令。它可以用来在程序中生成一个编译错误，并输出指定的错误信息。通常情况下，#error指令用于在编译时检查程序中的错误或不兼容性，以便在编译期间发现并解决问题。例如，以下代码片段使用#error指令来检查程序是否在32位平台上编译：
```
//#if sizeof(int) != 4
#ifdef __x86_64__
#error "This program requires a 32-bit platform."
#endif

[root@ubuntu0006:~] #gcc if_error_instruct_example.c
if_error_instruct_example.c:11:2: error: #error "This program requires a 32-bit platform."
 #error "This program requires a 32-bit platform."
  ^
if_error_instruct_example.c:22:2: error: #error "4 This program requires a 32-bit platform."
 #error "4 This program requires a 32-bit platform."
  ^
```
如果程序在64位平台上编译，编译器将生成一个错误消息，指出程序需要在32位平台上编译。

## 14、#if指令只支持常量表达式
C语言中的#if指令只支持常量表达式。常量表达式是指在编译时就可以计算出结果的表达式，例如整型字面量、枚举常量、sizeof运算符等。因为#if指令在预处理阶段执行，而预处理阶段是在编译阶段之前的，所以#if指令只能使用预处理器能够处理的常量表达式。

在预处理阶段使用非常量表达式是不可能的，因为预处理器只能处理常量表达式。预处理器是在编译器之前运行的，它的主要任务是处理以 # 开头的预处理指令，例如 #include 和 #define。预处理器只能处理常量表达式，例如整数、字符和字符串常量，因为它们的值在编译时就可以确定。非常量表达式的值只能在运行时确定，因此预处理器无法处理它们。

如果您需要在编译时使用非常量表达式，可以考虑使用编译器的优化选项。编译器可以在编译时对代码进行优化，以便在运行时计算非常量表达式的值。但是，这种优化可能会导致编译时间变长，因为编译器需要进行更多的计算。

实战代码见：D:\Github\Storage\c++\udev\remount_driver\if_error_instruct_example.c

## 15、通过预定义的宏来判断系统是32位还是64位
```
__x86_64__：如果该宏被定义，则表示当前系统是64位的x86架构。
_WIN64：如果该宏被定义，则表示当前系统是64位的Windows操作系统。
__LP64__：如果该宏被定义，则表示当前系统是64位的Unix或Linux操作系统。
```

如果以上宏都未被定义，则可以认为当前系统是32位的。例如，可以使用以下代码来判断当前系统的位数：
```
#ifdef __x86_64__
    printf("64-bit x86 architecture\n");
#elif _WIN64
    printf("64-bit Windows\n");
#elif __LP64__
    printf("64-bit Unix/Linux\n");
#else
    printf("32-bit system\n");
#endif
```
需要注意的是，以上宏定义并不是标准的C语言宏，而是由不同的编译器或操作系统提供的扩展。因此，在不同的平台上可能会有所不同。

## 16、替换成usbfs驱动
在usbredir库中，usbredirhost/usbredirhost.c文件的usbredirhost_set_device函数有此流程。
```
// 替换成usbfs驱动
int status = usbredirhost_set_device(host, dev_handle);

// 还原
int status = usbredirhost_set_device(host, NULL);
```
实战代码见：D:\Github\Storage\c++\udev\remount_driver\redir_udev_mount_usbfs_driver.c

## 17、usbfs驱动
libusb_set_auto_detach_kernel_driver函数是在libusb 1.0.16版本中引入的，因此只有在该版本或更高版本的libusb中才可用。
libusb_detach_kernel_driver函数是在libusb 0.1.8版本中引入的，因此只有在该版本或更高版本的libusb中才可用。

usbfs是Linux内核中的一种虚拟文件系统，用于与USB设备进行交互。它是一种用户空间和内核空间之间的接口，允许用户空间的应用程序通过文件系统API与USB设备进行通信。

在Linux系统中，usbfs驱动通常被挂载在/proc/bus/usb目录下。当用户空间的应用程序打开/proc/bus/usb目录下的某个文件时，usbfs驱动会将该文件映射到相应的USB设备上，并将USB设备的数据传输到用户空间的应用程序中。

usbfs驱动提供了一种简单而灵活的方式来访问USB设备，因为它允许用户空间的应用程序直接访问USB设备的原始数据。但是，由于usbfs驱动是一种虚拟文件系统，因此它的性能可能不如其他更专门的USB驱动程序。

需要注意的是，usbfs驱动已经被usbdevfs驱动所取代，后者提供了更好的性能和更多的功能。因此，在新的Linux系统中，usbfs驱动已经被弃用，而usbdevfs驱动则成为了主流的USB驱动程序。

## 18、usbdevfs驱动
usbdevfs驱动是在Linux内核2.3.15版本中引入的，用于与USB设备进行交互。它是一种用户空间和内核空间之间的接口，允许用户空间的应用程序通过文件系统API与USB设备进行通信。

libusb库从0.1.8版本开始支持usbdevfs驱动。在这个版本中，libusb库添加了对usbdevfs驱动的支持，使得用户空间的应用程序可以通过libusb库来访问USB设备。在此之前，libusb库只支持usbfs驱动。

需要注意的是，libusb库的不同版本对usbdevfs驱动的支持程度可能不同。在使用libusb库时，请务必仔细阅读相关文档和示例代码，以确保正确地使用API函数。

与usbfs驱动相比，usbdevfs驱动提供了更好的性能和更多的功能。例如，usbdevfs驱动支持异步I/O操作、USB设备的热插拔、USB设备的权限管理等功能。此外，usbdevfs驱动还提供了一些特殊的文件，例如/dev/usbmon，用于监视USB设备的数据流量。

没有相关过多的资料。

## 19、libusb和libusb1.0的区别
在libusb的发展历程中，从0.1.x版本开始，到1.0版本，API发生了一些变化，因此在1.0版本之后，libusb被称为libusb1.0。

## 20、整体操作流程
- 初始化libusb1.0库。可以使用libusb_init()函数来初始化libusb1.0库。

- 打开USB设备。可以使用libusb_open_device_with_vid_pid()函数来打开指定Vendor ID和Product ID的USB设备。

- 分离内核驱动程序。如果USB设备已经被内核驱动程序所占用，需要先将其分离。可以使用libusb_detach_kernel_driver()函数来分离内核驱动程序。

- 将设备挂载到usbdevfs驱动上。可以使用libusb_set_configuration()函数来设置USB设备的配置，然后使用libusb_claim_interface()函数来声明使用USB设备的接口。

- 进行USB数据传输。可以使用libusb_bulk_transfer()函数或libusb_interrupt_transfer()函数来进行USB数据传输。

- 关闭USB设备。可以使用libusb_release_interface()函数来释放USB设备的接口，然后使用libusb_close()函数来关闭USB设备。

- 退出libusb1.0库。可以使用libusb_exit()函数来退出libusb1.0库。


