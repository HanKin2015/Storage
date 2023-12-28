# python调用windows系统的dll文件
dll文件来源：D:\Github\Storage\windows\testdll\ArithmeticsDll

函数有：
```
double Add(double a, double b);
double Sub(double a, double b);
double Multi(double a, double b);
double Div(double a, double b);
int Export333();
int ExportN(int n);
```

## 1、查看dll文件位数
方法一：使用记事本查看，虽然不是很靠谱，但是好像还是有点作用：https://blog.csdn.net/bcbobo21cn/article/details/134376171
找到字符串PE，其后不远如果出现L，是32位;字符串PE后出现d?是64位。

方法二：使用dumpbin工具
```
D:\Users\User\Desktop>"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\dumpbin.exe" /headers mathematics.dll
Microsoft (R) COFF/PE Dumper Version 14.00.24210.0
Copyright (C) Microsoft Corporation.  All rights reserved.


Dump of file mathematics.dll

PE signature found

File Type: DLL

FILE HEADER VALUES
             14C machine (x86)
               6 number of sections
        657F05D6 time date stamp Sun Dec 17 22:29:42 2023
               0 file pointer to symbol table
               0 number of symbols
              E0 size of optional header
            2102 characteristics
                   Executable
                   32 bit word machine
                   DLL

OPTIONAL HEADER VALUES
             10B magic # (PE32)
```

## 2、OSError: [WinError 193] %1 不是有效的 Win32 应用程序
https://www.zhihu.com/question/353274186/answer/3177052270?utm_id=0
正解：https://www.coder.work/article/7506812
https://www.cnpython.com/qa/1287469
原因：64bit进程试图加载32bit.dll；32bit进程试图加载一个64bit.dll
结论：python是32位的，dll是64位的，可以安装64位的python，也可以将dll换成32位的。

最终切换32位版本的python环境执行调用dll文件成功。
```
64位python环境：
(base) D:\Users\User\Desktop>python
Python 3.7.6 (default, Jan  8 2020, 20:23:39) [MSC v.1916 64 bit (AMD64)] :: Anaconda, Inc. on win32
Type "help", "copyright", "credits" or "license" for more information.
>>>

32位python环境：
D:\Demo\Tools\python>python.exe
Python 3.8.6 (tags/v3.8.6:db45529, Sep 23 2020, 15:37:30) [MSC v.1927 32 bit (Intel)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>>

代码查看python环境位数：
import struct
print(struct.calcsize('P') * 8)
```
一般情况下，64 位的 Python 无法直接调用 32 位的 DLL 文件。这是因为 64 位的 Python 解释器和 32 位的 DLL 文件使用的是不同的指针大小和数据模型。

## 3、查看dll文件中的函数列表
使用ctypes库可以加载DLL文件并调用其中的函数，但是它无法直接列出DLL文件中的所有函数和方法。通常情况下，您需要查阅DLL文件的文档或者使用专门的工具来获取DLL文件中的函数和方法列表。

有一些工具可以帮助您获取DLL文件中的函数和方法列表。以下是其中一些常用的工具：
- Dependency Walker (depends.exe): Dependency Walker 是一个免费的工具，它可以用来查看 DLL 文件的导出函数列表。您可以使用它来打开 DLL 文件，然后查看其中包含的函数和方法。
- PE Explorer: PE Explorer 是一个功能强大的可执行文件编辑工具，它可以用来查看和编辑 DLL 文件。它提供了一个直观的界面，可以让您浏览 DLL 文件的导出函数列表。
- DLL Export Viewer: DLL Export Viewer 是一个小巧的免费工具，它可以列出 DLL 文件中的所有导出函数。您可以使用它来快速查看 DLL 文件中包含的函数和方法。
- IDA Pro: IDA Pro 是一个强大的逆向工程工具，它可以用来分析和查看 DLL 文件的导出函数列表，以及更深入的函数调用关系和代码分析。

确认depends.exe程序可以检测出dll文件中的函数列表。

## 4、无法直接调用dll文件中的类函数
找遍了所有资料，无法直接调用dll文件中的类函数，需要在dll文件中先创建类的实例，然后通过实例来调用类函数，这一点也区别于c/c++语言的调用。
https://www.cnblogs.com/night-ride-depart/p/4907613.html
https://www.cnblogs.com/FHC1994/p/11421229.html
https://www.auctoris.co.uk/2017/04/29/calling-c-classes-from-python-with-ctypes/
https://www.jianshu.com/p/0306a9898d68
https://blog.51cto.com/u_16175447/7598185
https://blog.51cto.com/u_16099237/7438747
https://blog.51cto.com/u_16213320/7394050

最终才找到问题原因：
ctypes库是用于调用C代码的工具，而不是C++代码。它可以与C代码进行交互，但无法直接调用C++代码。这是因为C++代码中包含了更复杂的特性，例如类、模板和异常处理等，而ctypes库无法直接处理这些特性。

如果您想调用C++代码，有几个可选的库可以考虑使用：
- Boost.Python：这是一个用于将C++代码封装为Python模块的库。它提供了一组工具和类，使您能够将C++类、函数和对象导出到Python中，并在Python中调用它们。
- SWIG（Simplified Wrapper and Interface Generator）：这是一个用于生成C++代码与多种高级语言（包括Python）之间的接口的工具。它可以自动生成用于将C++代码封装为Python模块的包装器代码。
- Pybind11：这是一个用于创建Python绑定的轻量级库。它提供了一组简单的C++宏和函数，使您能够将C++类、函数和对象导出到Python中，并在Python中调用它们。

https://blog.csdn.net/forcj/article/details/103249013
https://www.cnblogs.com/pam-sh/p/16203150.html

## 5、如何选择Python与C++之间的胶水：Boost.Python，Cython，pybind11，SWIG
http://www.manongjc.com/detail/41-becicsephmyccjh.html
https://www.zhihu.com/question/468279875/answer/2672324747
https://zyxin.xyz/blog/2019-08/glue-python-cpp/
https://www.zhihu.com/question/323926607/answer/2252290632
https://www.zhihu.com/question/285093492/answer/2776087035

总而言之，如果有多语言绑定的需求可以选择SWIG，如果有以下需求可以选择Cython，其他情况选择pybind11即可
- 需要保留模板参数，让用户可以自行选择用什么类型展开，或者目标用户有继续使用和拓展C++ API的需求时，用Cython便于用户使用
- 有大量的封装函数调用时，Cython的性能最好
- 绑定的对象是C语言写的API或者不涉及面向对象的话，那么用Cython写封装会更方便（不用处理编译的问题）

## 6、python调用C++--VS2015配置pybind11
参考：https://www.cnblogs.com/okmai77xue/p/17482483.html#top

### 6-1、安装pybind11
pip install pybind11==2.9
不指定版本安装，安装了高版本2.11不支持vs2015，最低支持vs2017

### 6-2、配置pybind11
- 创建项目并调整为release/x64，右键点击工程选择属性，配置属性>>常规>>配置 设置成dll
- 设置输出文件，一般 pyd 的导出文件名称就是项目的名称，因此，最开始项目名称和 module 名称要一致，否则 import 时会报找不到
- 配置属性>>VC++目录>>包含目录（C:\Users\User\anaconda3\pkgs\python-3.7.6-h60c2a47_2\include；C:\Users\User\anaconda3\Lib\site-packages\pybind11\include）使用everything软件搜索pybind11和python3.lib即可找到这两个文件夹，因为pybind11库里面需要包含python.h头文件，因此需要python库
- 配置属性>>VC++目录>>库目录（C:\Users\User\anaconda3\pkgs\python-3.7.6-h60c2a47_2\libs）
- 链接器>>输入>>附加依赖项 设置python相关依赖的lib，主要用的是python37.lib 和 python3.lib（这一步可省略）

然后使用demo就可以生成了，注意vs里面显示还是存在红色异常，但是不映射生成结果。生成Pybind11Example.pyd文件。

### 6-3、生成结果进行调用使用
vs项目：
demo：D:\Github\Storage\python\call_dll\pybind11_example.py




