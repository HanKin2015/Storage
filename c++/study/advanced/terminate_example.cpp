/*******************************************************************************
* 文 件 名: terminate_example.cpp
* 文件描述: 用于强制终止程序，通常在无法正常处理异常的情况下被自动调用，也可由程序员手动调用
* 备    注: 默认调用 std::abort，但可通过自定义处理器改变行为（例如先执行一些清理再调用 abort）
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <exception>
#include <iostream>
#include <cstdlib>  // 包含 std::abort

void critical_operation()
{
    if (/* 检测到致命错误 */ true) {
        std::cerr << "发生致命错误，终止程序\n";
        std::terminate();  // 手动触发终止
    }
}

// 自定义终止处理器
void my_terminate()
{
    std::cerr << "自定义终止处理：程序即将终止\n";
    std::abort();  // 通常最后调用 abort（默认行为）
}

int main()
{
    //critical_operation();
    
    // 设置自定义终止处理器
    std::set_terminate(my_terminate);
    
    throw std::runtime_error("测试");  // 触发 terminate，执行 my_terminate
    return 0;
}