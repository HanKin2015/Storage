更多内容可见：D:\Github\GitBook\gitbook\USBDevice\libusb.md

## 1、vs编译器警告（等级 1）C4026
使用形参表声明的函数
函数声明具有形参，而函数定义没有。 对此函数的后续调用将假定该函数不具有参数。

详细可点击链接：https://learn.microsoft.com/zh-cn/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4026?view=msvc-170&f1url=%3FappId%3DDev14IDEF1%26l%3DZH-CN%26k%3Dk(C4026)%26rd%3Dtrue

## 2、vs编译器警告（等级 1）C4005
“identifier”: 宏重新定义
该宏标识符定义了两次。 编译器使用第二个宏定义。

windows中内部有定义ERROR，因此写打印日志的时候需要注意。

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
