# OpenMP

## 1、简介
并行计算模型：并行计算模型是指在并行计算系统中，各个处理器或核心如何协同工作的规范。常见的并行计算模型有：分布式计算模型、共享内存模型和消息传递模型等。

并行计算框架：并行计算框架是一种软件架构，它提供了一种抽象的并行计算模型，以及一系列工具和库来实现并行计算任务。常见的并行计算框架有：Hadoop、Spark、MPI、OpenMP等。

并行计算任务：并行计算任务是指在并行计算系统中，各个处理器或核心同时执行的任务。并行计算任务可以是数据处理任务、计算任务、优化任务等。

并行计算任务的分解：在并行计算中，我们需要将原始任务分解为多个子任务，这些子任务可以在多个处理器或核心上并行执行。并行计算任务的分解可以是数据划分、任务划分、任务依赖等多种方式。

并行计算任务的调度：并行计算任务的调度是指在并行计算系统中，根据任务的优先级、资源需求等因素，将任务分配给各个处理器或核心执行的过程。并行计算任务的调度可以是静态调度、动态调度等多种方式。

OpenMP是一种共享内存并行计算算法，它允许我们在多线程环境中并行执行任务。OpenMP算法的核心步骤如下：
线程创建：在OpenMP算法中，我们需要创建多个线程，每个线程负责执行一部分任务。线程可以是独立的，也可以是依赖关系。
任务分配：在OpenMP算法中，我们需要将任务分配给多个线程执行。任务分配可以是数据划分、任务划分等多种方式。
同步：在OpenMP算法中，我们需要处理多线程之间的同步问题。同步可以是数据同步、任务同步等多种方式。

## 2、安装使用
Linux 系统完全支持 OpenMP（Open Multi-Processing），这是一种用于共享内存并行编程的标准 API，可显著提升多核处理器上的程序性能。

OpenMP 在 Linux 上的支持情况：
编译器支持：主流编译器（如 GCC、Clang）均内置 OpenMP 支持。
- GCC：从 4.2 版本开始支持 OpenMP，目前默认启用（需通过 -fopenmp 选项激活）。
- Clang：从 3.7 版本开始支持 OpenMP（需安装 libomp 库）。

操作系统：几乎所有 Linux 发行版（如 Ubuntu、CentOS、Debian）都预装了支持 OpenMP 的编译器。

测试demo：D:\interview\Storage\c++\高性能计算\OpenMP\omp_example.cpp

通过环境变量 OMP_NUM_THREADS 调整线程数，export OMP_NUM_THREADS=4
OMP_NUM_THREADS=4 ./test

## 3、clock()统计程序运行时不准确
测试发现使用clock()统计程序运行时间是不准确的，不推荐使用：
demo：D:\interview\Storage\c++\高性能计算\OpenMP\calculate_runtime_by_clock.cpp

不添加-fopenmp参数编译无法启动，测试发现就是使用的单核运行：
demo：D:\interview\Storage\c++\高性能计算\OpenMP\calculate_runtime_by_chrono.cpp
```
root@hankin:~/opencv# g++ main.cpp -fopenmp
root@hankin:~/opencv# ./a.out 
Number of threads: 1
Sum: -5340232216128654848
Code took 21515.8 milliseconds.
root@hankin:~/opencv# !ex
export OMP_NUM_THREADS=1
root@hankin:~/opencv# export OMP_NUM_THREADS=4
root@hankin:~/opencv# ./a.out 
Number of threads: 4
Sum: -5340232216128654848
Code took 5949.27 milliseconds.
root@hankin:~/opencv# ./a.out 
Number of threads: 4
Sum: -5340232216128654848
Code took 5876.2 milliseconds.
root@hankin:~/opencv# export OMP_NUM_THREADS=1
root@hankin:~/opencv# ./a.out 
Number of threads: 1
Sum: -5340232216128654848
Code took 21615.2 milliseconds.
```

## 5、问题error: invalid controlling predicate
`#pragma omp parallel for` 只能应用于可静态分析的循环结构，而你的循环条件 i <= 1e9 使用了浮点数常量 1e9，导致 OpenMP 无法静态确定迭代次数。

## 6、#pragma
在 C、C++ 等编程语言中，#pragma 是一个预处理指令，用于向编译器提供特殊的编译选项或行为控制。它的名称来源于 "pragmatic"（务实的），表示这是一种针对特定编译器实现的实用机制。