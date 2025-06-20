// CallDllFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <WinBase.h>
#include <libloaderapi.h>
#include <strsafe.h>
#include <iostream>

void bingo()
{
	// 添加 DLL 搜索目录
	//SetDllDirectory(L"C:\\Users\\User\\Downloads\\usbmagic\\usbmagic");
	//const wchar_t* dllPath = L"libusbmagic_ctrl.dll";

    // LoadLibraryEx函数无法解决
	const wchar_t* dllPath = L"C:\\Users\\User\\Downloads\\usbmagic\\usbmagic\\libusbmagic_ctrl.dll";
	//HMODULE hPagentDll = LoadLibrary(dllPath);
	//HMODULE hPagentDll = LoadLibraryEx(dllPath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
}

int main() 
{
	// 无问题的路径
	//const wchar_t* dllPath = L"C:\\Users\\User\\Downloads\\usbmagic\\usbmagic\\ArithmeticsDll.dll";

	// 有问题的路径，C前面有一个LRE字符（Left-to-Right Embedding）如 LRE、RLE、PDF 等 Unicode 控制字符
	// 使用notepad++显示所有字符能看出来，使用vs是看不出来的，但是可以通过把字符串打印可以看出字符串是否是正常的
	// 造成这个的主要原因是右键文件属性，然后拷贝安全选项卡中的对象名称导致
	const wchar_t* dllPath = L"‪C:\\Users\\User\\Downloads\\usbmagic\\usbmagic\\ArithmeticsDll.dll";
	HMODULE hPagentDll = LoadLibrary(dllPath);
	if (!hPagentDll)
	{
		// 无法打印宽字符串
		std::cout << dllPath << std::endl;
		printf("LoadLibrary dll失败(%ls)！错误码：%lu\n", dllPath, GetLastError());	// 正常
		printf("LoadLibrary dll失败(%lls)！错误码：%lu\n", dllPath, GetLastError());	// 异常
		printf("LoadLibrary dll失败(%Ls)！错误码：%lu\n", dllPath, GetLastError());	// 异常
		printf("LoadLibrary dll失败(%ws)！错误码：%lu\n", dllPath, GetLastError());	// 正常
		return -1;
	}
	std::cout << dllPath << std::endl;
	printf("LoadLibrary dll失败(%ls)！错误码：%lu\n", dllPath, GetLastError());
	printf("LoadLibrary dll失败(%lls)！错误码：%lu\n", dllPath, GetLastError());
	printf("LoadLibrary dll失败(%Ls)！错误码：%lu\n", dllPath, GetLastError());
	printf("LoadLibrary dll失败(%ws)！错误码：%lu\n", dllPath, GetLastError());

	FreeLibrary(hPagentDll);
	system("pause");
    return 0;
}

