/*******************************************************************************
* 文 件 名: calculate_runtime_by_class.cpp
* 文件描述: 将计时逻辑封装为类，使用更方便
* 备    注: 析构时自动输出时间
* 作    者: HanKin
* 创建日期: 2025.07.22
* 修改日期：2025.07.22
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <sys/time.h>

void task()
{
    std::cout << "start task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return;
}

class Timer
{
public:
    // 构造函数
    Timer(std::string name): m_name(name)
    {
        m_start = clock_t::now();
    }
    
    // 析构函数
    virtual ~Timer()
    {
        time_point_t end = clock_t::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start).count();
        if (!m_name.empty()) {
            std::cout << '[' << m_name << "] ";
        }
        std::cout << "Code took " << duration << " ms." << std::endl;
    }

private:
    using clock_t = std::chrono::high_resolution_clock;
    using time_point_t = clock_t::time_point;
    time_point_t m_start;
    std::string m_name;
};

int main()
{
    {
        Timer tmp("hankin");
        std::thread t(task);

        // 待计时的代码
        std::cout << "start main task..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        t.join();
    }

    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp
root@hankin:~/opencv# ./a.out 
start main task...
start task...
[hankin] Code took 3000 ms.
*/