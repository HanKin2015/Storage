/*******************************************************************************
* 文 件 名: GetOverlappedResult_example.c
* 文件描述: GetOverlappedResult函数是Windows API中的一个函数，用于获取异步I/O操作的结果
* 作    者: HanKin
* 创建日期: 2023.09.19
* 修改日期：2023.09.19
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main(int argc, char *argv[])
{
    HANDLE hFile = CreateFile(
        L"D:\\rvllog.log",
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,   // 使用FILE_FLAG_OVERLAPPED标志启用异步I/O功能
        NULL
        );

    OVERLAPPED overlapped = { 0 };
    char buffer[1024];
    DWORD bytesRead = 0;

    if (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, &overlapped)) {
        // 同步读取文件成功
        printf("synchronous read file success, %s\n", buffer);
    } else {
        if (GetLastError() == ERROR_IO_PENDING) {
            // 异步读取文件正在进行中
            if (GetOverlappedResult(hFile, &overlapped, &bytesRead, TRUE)) {
                // 异步读取文件成功
                printf("asynchronous read file success, %s\n", buffer);
            } else {
                // 异步读取文件失败
                printf("asynchronous read file failed, %s\n", buffer);
            }
        } else {
            // 异步读取文件失败
            printf("asynchronous read file failed, %s\n", buffer);
        }
    }

    CloseHandle(hFile);
    return 0;
}