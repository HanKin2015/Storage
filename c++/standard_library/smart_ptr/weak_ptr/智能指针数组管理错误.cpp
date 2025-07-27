/*******************************************************************************
* 文 件 名: 智能指针数组管理错误.cpp
* 文件描述: 使用 std::unique_ptr<int[]>（支持数组）
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.27
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <memory>

int main()
{
    // 错误：默认删除器使用delete而非delete[]
    std::shared_ptr<int> arr(new int[10]);
    
    // 析构时仅调用delete，导致数组内存泄漏
    return 0;
}