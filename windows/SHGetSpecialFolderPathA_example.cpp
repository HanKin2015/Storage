/*******************************************************************************
* 文 件 名: SHGetSpecialFolderPathA_example.cpp
* 文件描述: CSIDL 表示的是windows shell中一个特殊文件夹的标识值。这里说的特殊文件夹指的是由windows shell所定义的文件夹。
* 作    者: HanKin
* 创建日期: 2025.03.20
* 修改日期：2025.03.20
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <WinBase.h>
#include <libloaderapi.h>
#include <cstdio>

/**
 * @brief 获取当前用户appdata路径（即%appdata%所指向的路径）
 *        C:\Users\sangfor\AppData\Roaming
 * @return std::string
 */
#include <shlobj_core.h>
#include <ShlObj.h>
#pragma comment(lib, "Shell32.lib")
static std::string get_appdata_path()
{
    char buf[MAX_PATH] = { 0 };
    BOOL success = SHGetSpecialFolderPathA(NULL, buf, CSIDL_APPDATA, false);
    if (!success) {
        printf("get path of appdata failed, buf=%p, errno=%u\n", buf,
            GetLastError());
        return "";
    }
    printf("buf: %s\n", buf);
    return buf;
}

int main()
{
    std::cout << "Hello World!\n";
    HMODULE hPagentDll = LoadLibraryA("C:\\Program Files (x86)\\Core.dll");
    if (hPagentDll)
    {
        typedef ULONG(*FN_InitBaseEnv)();
        FN_InitBaseEnv InitBaseEnv = (FN_InitBaseEnv)GetProcAddress(hPagentDll, "ReadNodeConfigUtf8");
        if (InitBaseEnv)
        {
            printf("pRet = %p\n", InitBaseEnv);
        }
        else
        {
            printf("load ReadNodeConfigUtf8 fuction failed，err:%u.", GetLastError());
        }
    }
    else
    {
        printf("no\n");
    }

    get_appdata_path();
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
