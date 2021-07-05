// ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

#ifdef STATIC_USE
#include "studydll.h"
#pragma comment(lib, "Dll.lib")
#else
#include <Windows.h>
#endif // STATIC_USE

/*
由于C++导出Dll时会出现名字更改的问题，因此这里用序列号代表函数，至于函数的序列号可以用如下方法查看：

用VS打开cmd窗口（Tools --> Visual Studio Command Prompt），运行dumpbin -exports xxx.dll     后面最好写DLL的绝对路径，否则可能会报错LNK1181: cannot open input file 'XXX.dll'。

可在EXE所在的目录下使用dumpbin -imports xxx.EXE来查看某EXE文件使用过哪些dll库。

64位EXE尽量去调用64位DLL，同理32位尽量调用32位。

工具-》命令行-》开发者命令提示
输入dumpbin -exports Dll.dll

C:\Users\Administrator\source\repos\ConsoleApplication>dumpbin -exports Dll.dll
Microsoft (R) COFF/PE Dumper Version 14.29.30038.1
Copyright (C) Microsoft Corporation.  All rights reserved.


Dump of file Dll.dll

File Type: DLL

  Section contains the following exports for Dll.dll

    00000000 characteristics
    FFFFFFFF time date stamp
        0.00 version
           1 ordinal base
           5 number of functions
           5 number of names

    ordinal hint RVA      name

          1    0 000010D0 ?Add@arithmetic_operation@@QAENNN@Z = ?Add@arithmetic_operation@@QAENNN@Z (public: double __th
iscall arithmetic_operation::Add(double,double))
          2    1 00001100 ?Div@arithmetic_operation@@QAENNN@Z = ?Div@arithmetic_operation@@QAENNN@Z (public: double __th
iscall arithmetic_operation::Div(double,double))
          3    2 000010F0 ?Multi@arithmetic_operation@@QAENNN@Z = ?Multi@arithmetic_operation@@QAENNN@Z (public: double
__thiscall arithmetic_operation::Multi(double,double))
          4    3 000010E0 ?Sub@arithmetic_operation@@QAENNN@Z = ?Sub@arithmetic_operation@@QAENNN@Z (public: double __th
iscall arithmetic_operation::Sub(double,double))
          5    4 00001110 ?export333@@YAHXZ = ?export333@@YAHXZ (int __cdecl export333(void))

  Summary

        1000 .data
        1000 .rdata
        1000 .reloc
        1000 .rsrc
        1000 .text

可以看到1----Add、2----Div、3----Multi、4----Sub、5----export333
动态调用程序有低概率崩溃，但是所有值都正常输出。
*/

int main()
{
#ifdef STATIC_USE
    arithmetic_operation ao;
    cout << ao.Add(1, 2) << endl;
    cout << ao.Sub(2, 1) << endl;
    cout << ao.Multi(2, 1) << endl;
    cout << ao.Div(6, 4) << endl;
    cout << export333() << endl;
    cout << "Hello World!\n";
#else
    typedef int(*_print)();
    //typedef double(*_print)(double a, double b);
    cout << "1" << endl;
    HINSTANCE hDll = LoadLibrary(L"Dll.dll");
    if (!hDll) {
        cout << "Dll.dll file is not exist!" << endl;
        return -1;
    }
    cout << "2" << endl;
    // 函数的序列号调用见上面注解
    //_print pAdd = (_print)GetProcAddress(hDll, (LPCSTR)MAKEINTRESOURCE(4));
    //如果想要直接使用函数名，那么在生成DLL时要加extern "C"。但是它仍然有局限性，只针对函数，不针对类。
    _print pAdd = (_print)GetProcAddress(hDll, "export333");
    
    if (!pAdd) {
        cout << "GetProcAddress failed!" << endl;
        return -1;
    }
    cout << "3" << endl;
    double a = pAdd();
    cout << a << endl;
    cout << "Hello World!\n";
    FreeLibrary(hDll);
#endif // STATIC_USE

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
