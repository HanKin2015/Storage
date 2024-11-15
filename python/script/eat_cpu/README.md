# 吃CPU资源消耗小工具

## 1、Linux
stressstress-ng 是 stress 的增强版，提供了更多的测试选项和更细粒度的控制
stress-ng 是 stress 的增强版，提供了更多的测试选项和更细粒度的控制，stress-ng --cpu 4 --timeout 60s，将在 60 秒内使用 4 个 CPU 工作线程
sysbench cpu --cpu-max-prime=20000 run，将计算素数以消耗 CPU 资源

## 2、Windows
使用multiprocessing多进程直接运行没有问题，但是通过pyinstaller打包后存在内存泄露，从而导致系统卡死，不推荐。


