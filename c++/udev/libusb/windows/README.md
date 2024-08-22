# 在windows系统上获取usb设备信息

## 1、前言
由于一开始打算使用libusb库，因此部分内容见：D:\Github\GitBook\gitbook\USBDevice\libusb.md
LibusbExample：简单使用libusb库的例子
device_helper：计划使用libusb库获取usb设备信息，结果获取字符串描述符失败
UsbviewGetDescriptor：最终的成果，可行

## 2、无法解析的外部符号解决方法汇总
https://blog.csdn.net/wu_nan_nan/article/details/49838409

添加#pragma comment(lib, "libusb-1.0.lib")后还是无法解析。
出现这个问题，不用怀疑，一定是你没有包含lib库，或者没有正确包含lib库。何谓没有正确包含？32位的项目不能使用64位的lib，反之亦然；有时候Debug模式下生产的lib也不能共Release模式使用，反之亦然。

最终切换项目为x86后正常编译运行了。

## 3、调用 DeviceIoControl
https://learn.microsoft.com/zh-cn/windows/win32/devio/calling-deviceiocontrol?redirectedfrom=MSDN

## 4、GlobalAlloc函数
在Windows操作系统中，GlobalAlloc函数用于在进程的堆中分配指定大小的内存块，并返回一个指向该内存块的全局唯一句柄。该函数的声明如下：

c
HGLOBAL GlobalAlloc(
  UINT   uFlags,
  SIZE_T dwBytes
);
其中，参数uFlags指定内存分配的方式，可以是以下值之一：

GMEM_FIXED：分配固定内存，返回的句柄指向的内存块不会移动。
GMEM_MOVEABLE：分配可移动内存，返回的句柄指向的内存块可以移动。
GMEM_ZEROINIT：分配内存时将其初始化为0。
参数dwBytes指定要分配的内存块的大小，以字节为单位。

使用GlobalAlloc函数分配的内存块可以通过GlobalLock函数获取指向该内存块的指针，通过GlobalUnlock函数释放该指针。使用GlobalFree函数释放内存块。

需要注意的是，GlobalAlloc函数分配的内存块是在进程的堆中分配的，因此在使用完毕后需要及时释放，否则可能会导致内存泄漏。

## 5、内存句柄HGLOBAL报错，但是usbview源代码没有问题
原因是c语言和c++语言的问题。
另外还有就是在c语言中支持的语法，在c++中不支持。
```head.h
int h;
```

```main.cpp
#include <stdio.h>
#include "head.h"
int h = 10;

int main(int argc, char* argv[])
{
    return 0;
}
```

```main.c
#include <stdio.h>
#include "head.h"
int h = 10;

int main(int argc, char* argv[])
{
    return 0;
}
```

编译结果：
```
[root@ubuntu0006:~/cmake] #g++ main.cpp
main.cpp:13:5: error: redefinition of ‘int h’
 int h = 10;
     ^
In file included from main.cpp:12:0:
head.h:1:5: note: ‘int h’ previously declared here
 int h;
     ^
[root@ubuntu0006:~/cmake] #gcc main.c
[root@ubuntu0006:~/cmake] #g++ main.c
main.c:13:5: error: redefinition of ‘int h’
 int h = 10;
     ^
In file included from main.c:12:0:
head.h:1:5: note: ‘int h’ previously declared here
 int h;
     ^
```

## 6、项目配置
另外就是属性配置了，设置警告转换为错误等等，这个还挺好用的，跟着usbview项目设置即可。

## 7、链接错误
这个我终于明白了，无非就是函数定义了，但是未找到函数的实现内容。
如在头文件中声明定义了function函数，然后在实际过程中进行使用，则就会报链接错误。
解决方法：
自定义函数就自己去实现，内部函数则需要添加lib文件，一个是在属性-》链接器-》输入中添加，另外则是使用代码添加：
```
#pragma comment(lib, "setupapi.lib")
```

## 8、vs添加第三方库文件夹
属性-》C/C++-》常规-》附加包含目录

## 9、RapidJSON无法在纯C项目中使用
http://rapidjson.org/zh-cn/

RapidJSON 是一个 C++ 库，因此在纯 C 项目中直接使用会有一些问题，因为 C 不支持命名空间（namespace）的概念。

如果您的项目是纯 C 项目，而不是 C++ 项目，那么您无法直接使用 RapidJSON 库。在这种情况下，您可以考虑使用其他专门为 C 语言设计的 JSON 解析库，例如 cJSON 或 Jansson。这些库提供了纯 C 的 API，可以方便地在 C 项目中使用。

如果您的项目是 C++ 项目，那么您可以使用 RapidJSON 库，并在代码中使用命名空间来访问其功能。在 C++ 项目中，您可以包含 RapidJSON 的头文件，并使用其提供的类和函数来解析和生成 JSON 数据。

选择使用cJSON，项目更加小巧。
demo见：D:\Github\Storage\c++\parse\cjson\cJSON_example.c

## 10、获取hid设备字符串描述符失败（指的是翻译出来的字符串，而不是raw）
设备是一个hid类型ukey，465a:1053。
最终发现是设备问题，在物理机上面使用开源的usbview软件多次获取会出现获取失败：String Descriptor for index 4 not available while device is in low power state.

参考usbview的代码编写的程序同样的效果，拔插一开始能正常获取几次字符串描述符，后面就会失败。
一开始我以为是代码问题，有缺陷获取不到字符串描述符。于是在网上找了使用HidD_GetProductString函数获取的方法，结果更糟糕，从来没有获取成功。但是这个函数是有作用的，在测试了其他的键盘、鼠标、指纹仪都能获取成功。对于此ukey表现只会比usbview的方法更差。

demo见：D:\Github\Storage\c++\udev\libusb\windows\GetHidAttribute.c
exe见：D:\Github\Storage\c++\udev\libusb\windows\GetHidAttribute.exe

## 11、vs编译器警告（等级 1）C4026
使用形参表声明的函数
函数声明具有形参，而函数定义没有。 对此函数的后续调用将假定该函数不具有参数。

详细可点击链接：https://learn.microsoft.com/zh-cn/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4026?view=msvc-170&f1url=%3FappId%3DDev14IDEF1%26l%3DZH-CN%26k%3Dk(C4026)%26rd%3Dtrue

## 12、vs编译器警告（等级 1）C4005
“identifier”: 宏重新定义
该宏标识符定义了两次。 编译器使用第二个宏定义。

windows中内部有定义ERROR，因此写打印日志的时候需要注意。
