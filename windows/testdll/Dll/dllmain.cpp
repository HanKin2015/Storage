// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <cstdio>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    printf("hModule.%p lpReserved.%p \n", hModule, lpReserved);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        printf("Process attach. \n");
        break;
    case DLL_PROCESS_DETACH:
        printf("Process detach. \n");
        break;
    case DLL_THREAD_ATTACH:
        printf("Thread attach. \n");
        break;
    case DLL_THREAD_DETACH:
        printf("Thread detach. \n");
        break;
    }
    return TRUE;
}

