// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <io.h>

/*
D:\Users\User\Desktop\config.json
D:\Users\User\Desktop\config.json file not exist.
j = 10
*/
static void access_example()
{
#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */

    const char *file_path = "D:\\Users\\User\\Desktop\\config.json";
    printf("%s\n", file_path);
    if (!access(file_path, F_OK)) {
        printf("%s file exist.\n", file_path);
    } else {
        printf("%s file not exist.\n", file_path);
    }

    int j = 0;
    for (j = 0; j < 10; j++);
    {
        printf("j = %d\n", j);
    }
    return;
}

/*
D:\Users\User\My Document\Visual Studio 2010\Projects\test\Release>test.exe -p jk -o hj
命令行参数: test.exe  -p jk -o hj
*/
static void GetCommandLine_example1()
{
	LPTSTR lpCmdLine = GetCommandLine();
	printf("命令行参数: %ls\n", lpCmdLine);
	return;
}

/*
D:\Users\User\My Document\Visual Studio 2010\Projects\test\Release>test.exe -p jk -o hj
0: test.exe
1: -p
2: jk
3: -o
4: hj
*/
static void GetCommandLine_example2()
{
	LPWSTR *szArglist;
	int nArgs;
	int i;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (NULL == szArglist)
	{
		wprintf(L"CommandLineToArgvW failed\n");
		return;
	}
	else
	{
		for( i=0; i<nArgs; i++)
		{
			printf("%d: %ws\n", i, szArglist[i]);
		}
		LocalFree(szArglist);// Free memory allocated for CommandLineToArgvW arguments.
	}
	return;
}

LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (p1 != NULL && *p1 != NULL)
	{
		LPCTSTR p = p2;
		while (p != NULL && *p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1 = CharNext(p1);
	}
	return NULL;
}

/*
D:\Users\User\My Document\Visual Studio 2010\Projects\test\Release>test.exe -p jk 3 4 -path hj 5 6 -open
lpszToken: p jk 3 4 -path hj 5 6 -open
lpszToken: path hj 5 6 -open
lpszToken: open
open
*/
static void GetCommandLine_example3()
{
	LPTSTR lpCmdLine = GetCommandLine();
	TCHAR szTokens[] = _T("-/");

	LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		printf("lpszToken: %ls\n", lpszToken);
		if (lstrcmpi(lpszToken, _T("path")) == 0)
		{
			printf("path\n");
		}
		if (lstrcmpi(lpszToken, _T("open")) == 0)
		{
			printf("open\n");
		}

		lpszToken = FindOneOf(lpszToken, szTokens);
	}
}

/*
D:\Users\User\My Document\Visual Studio 2010\Projects\test\Release>test.exe -p jk656
0: test.exe
1: -p
2: jk656
file path: jk656
invalid file path name!
D:\Users\User\My Document\Visual Studio 2010\Projects\test\Release>test.exe -p jk65
0: test.exe
1: -p
2: jk65
file path: jk65
*/
#define COMMAND_LINE_PARAMETERS 3	//命令行参数必须是2个，第二个参数是文件存储路径
#define MAX_FILE_PATH_NAME 4		//最长路径名
static int GetCommandLine_example4()
{
    LPWSTR *szArglist = NULL;
	int nArgs = 0;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (szArglist == NULL)
	{
		printf("CommandLineToArgvW failed\n");
		return -1;
	}
	else
	{
		if (nArgs != COMMAND_LINE_PARAMETERS)
		{
			printf("params are not three!\n");
			return -1;
		}
		for (int i = 0; i < nArgs; i++)
		{
			printf("%d: %ws\n", i, szArglist[i]);
		}
		if (lstrcmpi(szArglist[1], _T("-p")) == 0)
		{
			printf("file path: %ws\n", szArglist[2]);
			if (wcslen(szArglist[2]) > MAX_FILE_PATH_NAME) {
				printf("invalid file path name!");
				return -1;
			}
		}
		LocalFree(szArglist);
		szArglist = NULL;
	}
    return 0;
}

/*
真没有想明白，花费大量时间在干什么
D:\Users\User\My Document\Visual Studio 2010\Projects\test\Release>test.exe -p jk65
argc: 3
0: test.exe
1: -p
2: jk65
file path: jk65

D:\Users\User\My Document\Visual Studio 2010\Projects\test\Release>test.exe -p jk65f
argc: 3
0: test.exe
1: -p
2: jk65f
file path: jk65f
invalid file path name!
*/
static int GetCommandLine_example5()
{
	printf("argc: %d\n", argc);
	if (argc != COMMAND_LINE_PARAMETERS)
	{
		printf("params are not three!\n");
		return -1;
	}

	for (int i = 0; i < argc; i++)
	{
		printf("%d: %ws\n", i, argv[i]);
	}

	if (lstrcmpi(argv[1], _T("-p")) == 0)
	{
		printf("file path: %ws\n", argv[2]);
		if (wcslen(argv[2]) > MAX_FILE_PATH_NAME) {
			printf("invalid file path name!");
			return -1;
		}
	}
    return 0;
}

/*
path1 is empty
path2 is not empty
*/
static void empty_example()
{
	std::string path1 = "";
	std::string path2 = "2222";
	if (path1.empty())
	{
		printf("path1 is empty\n");
	}
	else
	{
		printf("path1 is not empty\n");
	}
	if (path2.empty())
	{
		printf("path2 is empty\n");
	}
	else
	{
		printf("path2 is not empty\n");
	}
    return;
}

// 要将"WCHAR *"转换为"const char *"，您需要进行字符编码的转换。可以使用一些函数来完成这个转换，例如WideCharToMultiByte函数。
static void WideCharToMultiByteExample()
{
    // 假设有一个"WCHAR *"字符串
    WCHAR* wideStr = L"宽字符字符串";

    // 计算所需的缓冲区大小
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);

    // 分配缓冲区
    char* buffer = new char[bufferSize];

    // 进行字符编码转换
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, buffer, bufferSize, NULL, NULL);

    // 将转换后的字符串打印出来
    std::cout << buffer << std::endl;

    // 释放缓冲区内存
    delete[] buffer;
}

// CharLowerBuff 函数只能处理以 null 结尾的字符串，而不能处理 Unicode 字符串。如果您需要处理 Unicode 字符串，可以使用 CharLowerBuffW 函数(将字符串转换为小写的函数)
#include <Winbase.h>
static void CharLowerBuffExample()
{
    TCHAR str[] = TEXT("Hello, World!");

    CharLowerBuff(str, lstrlen(str));

    // 输出转换后的字符串
    _tprintf(TEXT("%s\n"), str);
    return;
}

int _tmain(int argc, _TCHAR* argv[])
{


    system("pause");
    return 0;
}
