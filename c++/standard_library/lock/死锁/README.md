# gdb调试排查死锁

## 1、top命令
```
top -H -p 8047
使用h查看帮助，使用H查看线程情况
如果一个进程包含两个线程，那么它的线程数量为3
```

## 2、gdb排查
```
启动 GDB 并附加到进程: gdb -p 8047
暂停程序执行: interrupt
查看线程信息: info threads
检查线程堆栈: thread apply all bt
```