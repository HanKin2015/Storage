## 1. 启动 gdb 时直接指定参数（推荐）
```
root@hankin:~/opencv# gdb --args a.out out.txt -v
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
--Type <RET> for more, q to quit, c to continue without paging--
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from a.out...
(gdb) r
Starting program: /root/opencv/a.out out.txt -v

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.ubuntu.com>
Enable debuginfod for this session? (y or [n]) 
Debuginfod has been disabled.
To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
argc = 3
/root/opencv/a.out
out.txt
-v
[Inferior 1 (process 164100) exited normally]
(gdb) show args
Argument list to give program being debugged when it is started is "out.txt -v".
```

## 2. 在 gdb 内部设置参数
如果已经进入 gdb 环境（未运行程序），可以用 set args 命令
```
(gdb) show args
Argument list to give program being debugged when it is started is "out.txt -v".
(gdb) set args data.csv 100
(gdb) show args
Argument list to give program being debugged when it is started is "data.csv 100".
(gdb) r
Starting program: /root/opencv/a.out data.csv 100
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
argc = 3
/root/opencv/a.out
data.csv
100
[Inferior 1 (process 164191) exited normally]
```

## 3. file命令
file命令可以加载二进制文件
```
root@hankin:~/opencv# gdb
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
--Type <RET> for more, q to quit, c to continue without paging--
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb) show args
Argument list to give program being debugged when it is started is "".
(gdb) r
Starting program:  
No executable file specified.
Use the "file" or "exec-file" command.
(gdb) file ./a.out 
Reading symbols from ./a.out...
(gdb) r
Starting program: /root/opencv/a.out 

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.ubuntu.com>
Enable debuginfod for this session? (y or [n]) 
Debuginfod has been disabled.
To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
argc = 1
/root/opencv/a.out
[Inferior 1 (process 164339) exited normally]
```

## 3. 运行时临时指定参数
执行 run（或缩写 r）命令时直接附加参数，临时覆盖之前的设置：
```
接上文
(gdb) r 1 2 3 fg
Starting program: /root/opencv/a.out 1 2 3 fg
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
argc = 5
/root/opencv/a.out
1
2
3
fg
[Inferior 1 (process 164410) exited normally]
```

## 总结
单次调试：用 gdb --args 程序 参数 最方便。
多次调试同一组参数：进入 gdb 后用 set args 固定参数。
临时换参数：直接用 run 参数 覆盖。
