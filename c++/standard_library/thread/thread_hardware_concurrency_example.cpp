/*******************************************************************************
* 文 件 名: thread_hardware_concurrency_example.cpp
* 文件描述: 获取当前计算机的CPU核心数，根据这个结果在程序中创建出数量相等的线程
* 备    注: g++ thread_example.cpp -lpthread -std=c++11
* 作    者: HanKin
* 创建日期: 2024.08.27
* 修改日期：2024.08.27
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
using namespace std;

int main()
{
    int num = thread::hardware_concurrency();
    cout << "CPU number: " << num << endl;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
CPU number: 2
[root@ubuntu0006:~/cmake] #lscpu
Architecture:          x86_64
CPU 运行模式：    32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                2
On-line CPU(s) list:   0,1
每个核的线程数：1
每个座的核数：  2
Socket(s):             1
NUMA 节点：         1
厂商 ID：           GenuineIntel
CPU 系列：          6
型号：              15
Model name:            Intel(R) Core(TM)2 Duo CPU     T7700  @ 2.40GHz
步进：              11
CPU MHz：             2900.000
BogoMIPS:              5800.00
超管理器厂商：  KVM
虚拟化类型：     完全
L1d 缓存：          32K
L1i 缓存：          32K
L2 缓存：           4096K
NUMA node0 CPU(s):     0,1
Flags:                 fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx lm constant_tsc rep_good nopl tsc_known_freq pni ssse3 cx16 pcid sse4_2 x2apic hypervisor lahf_lm kaiser
*/