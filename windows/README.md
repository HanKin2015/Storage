# windows编程

## 1、_T 
_T是一个宏，作用是让程序支持Unicode编码。因为Windows使用两种字符集ANSI和UNICODE，前者就是通常使用的单字节方式，但这种方式处理像中文这样的双字节字符不方便，容易出现半个汉字的情况。而后者是双字节方式，方便处理双字节字符。

## 2、重点在于StudyWindowsCLanguage项目
学习windows版本的C/C++语言。

## 3、MFC和Win32窗口程序有什么不同
MFC（Microsoft Foundation Class）和Win32窗口程序是Windows平台上的两种不同的应用程序开发框架。

MFC是微软提供的面向对象的应用程序框架，它封装了大量的Windows API功能，并提供了一系列的类库，使得开发者可以更加方便地创建Windows应用程序。MFC提供了诸如窗口管理、消息处理、用户界面控件等方面的封装，使得开发者可以更加专注于应用程序的逻辑而不必过多关注底层的API调用。

Win32窗口程序则是直接使用Windows API进行开发的传统方式。开发者需要手动处理诸如窗口过程、消息循环、窗口创建和管理等底层细节。

因此，MFC相对于Win32窗口程序来说，提供了更高层次的抽象和封装，使得开发者可以更快速地开发Windows应用程序，而Win32窗口程序则更加灵活，但需要开发者处理更多的底层细节。

MFC：D:\Github\Storage\windows\MFCApplication
Win32：D:\Github\Storage\windows\Win32Project

## 4、精简化创建MFC项目
在创建的时候，在应用程序类型选择基于对话框即可。
选择rc文件还是即时看见界面当前情况。

## 5、找了很多资料显示只能通过和hub进行io通信
https://blog.csdn.net/code_xxl/article/details/39343085
https://blog.csdn.net/qq_23867503/article/details/85463675
https://www.coder.work/article/7955478#google_vignette

## 6、加载dll文件
见项目：D:\Github\Storage\windows\testdll

## 7、MFC和Win32窗口程序缺少VCRUNTIME140D.dll文件
很奇怪，同事创建的MFC文件就不缺少，我看也应该是vs2015项目啊。
```
D:\Users\Visual Studio 2015\Projects\MFCApplication\Debug>objdump -x MFCApplication.exe | findstr "\.dll"
        DLL Name: mfc140ud.dll
        DLL Name: KERNEL32.dll
        DLL Name: USER32.dll
        DLL Name: GDI32.dll
        DLL Name: COMCTL32.dll
        DLL Name: OLEAUT32.dll
        DLL Name: gdiplus.dll
        DLL Name: VCRUNTIME140D.dll
        DLL Name: ucrtbased.dll

D:\Users\User\Desktop>objdump -x DetecTool.exe | findstr "\.dll"
        DLL Name: KERNEL32.dll
        DLL Name: USER32.dll
        DLL Name: GDI32.dll
        DLL Name: MSIMG32.dll
        DLL Name: ADVAPI32.dll
        DLL Name: SHELL32.dll
        DLL Name: COMCTL32.dll
        DLL Name: SHLWAPI.dll
        DLL Name: UxTheme.dll
        DLL Name: ole32.dll
        DLL Name: OLEAUT32.dll
        DLL Name: oledlg.dll
        DLL Name: gdiplus.dll
        DLL Name: OLEACC.dll
        DLL Name: IMM32.dll
        DLL Name: WINMM.dll
```

然后灵机一动，同时打开这两个项目，然后点击属性查看发现：配置属性=》常规=》项目默认值=》MFC的使用，从在共享DLL中使用MFC改成在静态库中使用MFC即可。（exe文件也可以这样操作，将使用标准Windows库改成在静态库中使用MFC）
重新编译生成后从206KB大小文件到9.88MB，这时候是Debug版本，改成Release版本后变成3.38MB大小。
```
D:\Users\Visual Studio 2015\Projects\MFCApplication\Debug>objdump -x MFCApplication.exe | findstr "\.dll"
        DLL Name: KERNEL32.dll
        DLL Name: USER32.dll
        DLL Name: GDI32.dll
        DLL Name: MSIMG32.dll
        DLL Name: ADVAPI32.dll
        DLL Name: SHELL32.dll
        DLL Name: COMCTL32.dll
        DLL Name: SHLWAPI.dll
        DLL Name: UxTheme.dll
        DLL Name: ole32.dll
        DLL Name: OLEAUT32.dll
        DLL Name: oledlg.dll
        DLL Name: gdiplus.dll
        DLL Name: OLEACC.dll
        DLL Name: IMM32.dll
        DLL Name: WINMM.dll
```

## 8、HeapAlloc分配内存后释放函数
在C/C++中，如果使用HeapAlloc函数分配内存，则需要使用HeapFree函数来释放内存。HeapAlloc和HeapFree是配对使用的，用于在堆上分配和释放内存。

例如，在使用HeapAlloc分配内存后，需要使用HeapFree来释放内存，示例代码如下：
```
LPVOID lpMem = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
// 使用分配的内存
// ...
HeapFree(GetProcessHeap(), 0, lpMem);
```
在这个示例中，HeapAlloc用于分配内存，然后在不再需要这块内存时，使用HeapFree来释放内存。

## 9、获取驱动程序信息
http://cn.voidcc.com/question/p-bxbodamg-bcg.html#google_vignette
https://blog.csdn.net/haart/article/details/120709158

（1）驱动路径获取方法
可见驱动路径是通过读取注册表

HKEY_LOCAL_MACHINE\SYSTEM\ControlSet\services\usbccgp项的ImagePath子项来获取的。

HKEY_LOCAL_MACHINE\SYSTEM\ControlSet\services是固定位置，usbccgp是设备的service属性值，可以通过调用SetupDiGetDeviceRegistryProperty传参SPDRP_SERVICE来获得。

HKEY_LOCAL_MACHINE\SYSTEM\ControlSet\services下包含一些列的驱动服务子项，每项下面都有ImagePath这一子项，包含了驱动的路径。

（2）inf文件位置
inf文件位置是通过读取HKEY_LOCAL_MACHINE\CurrentControlSet\Control\Class\{4d36e972-e325-11ce-bfc1-08002be10318}\0009下的InfPath子项得到。

HKEY_LOCAL_MACHINE\CurrentControlSet\Control\Class\是固定位置

{4d36e972-e325-11ce-bfc1-08002be10318}\0009是设备的DriverKey，可以通过调用SetupDiGetDeviceRegistryProperty传参SPDRP_DRIVER来获得。

https://blog.csdn.net/dybb8999/article/details/73606096
提供了打印中文的方法。

另外发现usbtreeview软件有显示sys路径，但是也仅仅是通过注册表读取的信息，只显示了主驱动程序。另外usbtreeview并没有开源。
它也无法阻止USB设备加载其他的驱动，因为有多个筛选器驱动程序（如前述的UpperFilters和LowerFilters），它们在主驱动程序的基础上提供额外的功能或处理。

demo见：D:\Github\Storage\windows\GetUsbDeviceDriverInfo
