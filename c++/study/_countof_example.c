/**
* 文 件 名: _countof_example.c
* 文件描述: _countof()函数及用法，windows独有
* 作    者: HanKin
* 创建日期: 2022.10.24
* 修改日期：2022.10.24
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>

/* _countof helper */
#if !defined(_countof)
    #if !defined(__cplusplus)
        #define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
    #else
        extern "C++"
        {
        template <typename _CountofType, size_t _SizeOfArray>
        char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
        #define _countof(_Array) sizeof(*__countof_helper(_Array))
        }
    #endif
#endif
 
int main(int argc, char *argv[])
{
    int arr[10];
    printf("%d\n", _countof(arr));
    return 0;
}