/*******************************************************************************
* 文 件 名: gdb_argument.cpp
* 文件描述: gdb调试添加参数
* 备    注: 编译的时候添加-g参数
* 作    者: HanKin
* 创建日期: 2025.09.02
* 修改日期：2025.09.02
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "argc = " << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    return 0;
}
