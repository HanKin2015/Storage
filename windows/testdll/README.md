# dll文件相关知识

## 1、dll文件注册表
dll文件查询位置：计算机\HKEY_CLASSES_ROOT\WOW6432Node\CLSID\{E0F6E061-5558-438D-9FA2-5C5503951000}\InprocServer32
{E0F6E061-5558-438D-9FA2-5C5503951000}来源：计算机\HKEY_CLASSES_ROOT\CoreVDI.CoreCom\CLSID

## 2、dll文件相关头文件
```
#include <Windows.h>
#include <WinBase.h>
#include <libloaderapi.h>
#include <shlobj_core.h>
#include <ShlObj.h>
#pragma comment(lib, "Shell32.lib")
```

## 3、dll文件内部函数查询
dumpbin.exe是微软二进制文件转储器。显示有关通用对象文件格式 (COFF) 的二进制文件的信息。
可以使用 DUMPBIN 检查 COFF 对象文件、 COFF 对象、 可执行文件和动态链接库 (Dll) 的标准库。

我的电脑VS安装路径是C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\dumpbin.exe。

也可以通过通过开始菜单里面的VisualStudio开发人员命令提示来运行。
```
C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64>dumpbin /export
s "C:\Users\Administrator\Desktop\Core.dll" | findstr Read
         24   AC 0003C570 ReadNodeAttrConfig
        172   AD 0003C610 ReadNodeAttrConfigUtf8
         23   AE 0003C490 ReadNodeConfig
        174   AF 0003C4E0 ReadNodeConfigUtf8
```

## 4、深坑
右键文件属性，然后拷贝安全选项卡中的对象名称会导致路径异常，路径最前面会有LRE、RLE、PDF 等 Unicode 控制字符。

当dll文件存在自定义的其他dll文件依赖的时候，在加载dll文件时会出现其他dll文件找不到的情况，这时候加载dll文件会报126错误，解决方式如下：
方法 1：使用 SetDllDirectory
方法 2：使用 PATH 环境变量
方法 3：将 DLL 放在 EXE 目录下

exe文件缺失dll文件依赖直接运行就能看出来，但是dll文件缺失依赖则是需要通过DEPENDS.EXE文件来查看。


