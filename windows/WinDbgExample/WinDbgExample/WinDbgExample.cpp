// WinDbgExample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

int main()
{
	srand(time(NULL));
	const CHAR *pContent = "123456789123456789123456789123456789";
	printf("pContent size: %d\n", strlen(pContent));
	for (int i = 0; i < 10; i++)
	{
		DWORD dSize = rand() % 20;
		printf("%lu\n", dSize);

		CHAR *pDest = (CHAR *)malloc(dSize + 1);
		memset(pDest, 0, dSize + 1);	// 如果不初始化为0则会打印乱码
		strncpy(pDest, pContent, dSize);// 注意strncpy拷贝时需要-1
		printf("%s\n", pDest);
		free(pDest);
		pDest = NULL;
	}
	CharLowerBuff(LPTSTR(pContent), strlen(pContent));	// 类型不匹配会导致程序崩溃踩内存
	char *AnsiName = (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH);
	if (AnsiName)
	{
		HeapFree(GetProcessHeap(), 0, AnsiName);
		printf("HeapAlloc success\n");
		AnsiName = NULL;
	}
	else
	{
		printf("HeapAlloc failed\n");
	}
    return 0;
}

