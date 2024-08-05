最开始是在Android8.1.0下面开发。

后续参考修改衍生了debian8和Android4.2.2两个版本。

## 20230322
- 脚本防止被kill掉后内存泄露
- 脚本是否可以防止多个相同名称运行

## 开机自启动
安卓系统：custom_boot.sh
debian系统：autostart.sh

## debian10新增预防多开
发现：pgrep 命令在搜索进程名时存在长度限制。具体的限制取决于操作系统和版本。

在大多数常见的操作系统中，进程名的长度限制通常是 15 个字符。这是因为在许多操作系统中，进程名存储在固定长度的数据结构中，以便高效地管理进程。

如果进程名超过了长度限制，pgrep 命令可能无法正确匹配进程名，导致无法找到对应的进程。

如果你需要搜索较长的进程名，可以考虑使用其他方法，如结合 ps 命令和 grep 命令来实现更灵活的进程搜索。例如，可以使用 ps -ef | grep <进程名> 来搜索进程名。这种方法不受进程名长度限制的影响。
```
[root@ubuntu0006:~] #!ps
ps aux | grep limit
root     19974  0.0  0.0  15400  3156 pts/8    T    15:17   0:00 /bin/bash ./limit_file_size.sh
root     20369  0.0  0.0  15400  3068 pts/8    T    15:17   0:00 /bin/bash ./limit_file_size.sh
root     22187  0.0  0.0  15400  3044 pts/8    T    15:18   0:00 /bin/bash ./limit_file_size_hjhjhj.sh
root     22671  0.0  0.0  15400  3048 pts/8    T    15:18   0:00 /bin/bash ./limit_file_size_hjhjhj.sh
root     24969  0.0  0.0  15400  3072 pts/8    T    15:19   0:00 /bin/bash ./limit_file_sizee.sh
root     25106  0.0  0.0  15400  2984 pts/8    T    15:19   0:00 /bin/bash ./limit_file_sizee.sh
root     25225  0.0  0.0  17088   972 pts/8    S+   15:19   0:00 grep --color=auto limit
[root@ubuntu0006:~] #pgrep limit_file_sizee
[root@ubuntu0006:~] #pgrep limit_file_size
19974
20369
22187
22671
24969
25106
```

## 解决打包脚本有部分抓包数据保留在缓冲区的问题
--line-buffered 是一个用于命令行工具的选项，它用于实现行缓冲输出。通常，标准输出会根据缓冲区的大小进行缓冲，直到达到一定条件（如缓冲区满或遇到换行符）才会将内容输出到终端。

使用 --line-buffered 选项可以改变这种行为，使得每次输出都会立即刷新到终端，而不需要等待缓冲区满或遇到换行符。这对于需要实时查看输出的情况非常有用，特别是在处理实时日志或其他动态输出时。

例如，假设有一个命令 command，你可以通过以下方式使用 --line-buffered 选项：
```
command --line-buffered
```
这样，command 的输出将会以行缓冲的方式进行，每次输出都会立即刷新到终端。

需要注意的是，并非所有的命令都支持 --line-buffered 选项，这取决于具体的命令行工具。你可以查阅命令的文档或使用 man 命令来了解特定命令是否支持该选项。

## 其实可以使用logrotate命令来限制文件大小
/etc/logrotate.d/rsyslog
```
/var/log/camera_clnt.log
/var/log/camera_tool.log
{
        rotate 2
        size 2M
        missingok
        notifempty
        compress
}
```

