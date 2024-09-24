# 在 Linux 系统中使用 C 程序调用 shell 命令

## 1、system与exec的区别
1、system（）和exec（）都可以执行进程外的命令，system是在原进程上开辟了一个新的进程，但是exec是用新进程（命令）覆盖了原有的进程
2、system（）和exec（）都有能产生返回值，system的返回值并不影响原有进程，但是exec的返回值影响了原进程

```
char cmd[MAX_BUF_LEN];
memset(cmd, 0, MAX_BUF_LEN);
snprintf(cmd, MAX_BUF_LEN, "mkdir -p %s", today_dir_path);
pid_t status = system(cmd);

if (!(status != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
	printf("system error, exit status value");
}
```

## 2、system函数
```
#include <stdlib.h>
int system(const char *command);
```
- 参数: command - 要执行的命令字符串。
- 返回值: 这个函数返回命令的退出状态或错误码。如果出错，返回-1。如果成功执行命令但命令失败，则返回命令的退出状态。

代码见：D:\Github\Storage\c++\get_result\system_example.c

## 3、popen函数
```
#include <stdio.h>
FILE *popen(const char *command, const char *type);
```
- 参数:
    - command - 要执行的命令字符串。
    - type - 指定模式，通常是"r"（读取模式）或"w"（写入模式）。
- 返回值: 如果成功，则返回一个文件指针，该指针可以用于读取命令的输出（当type为"r"时）或向命令写入数据（当type为"w"时）。如果出错，返回NULL。

代码见：D:\Github\GitBook\gitbook\Tools\popen_example.c

## 4、C 中的 exec 系列函数
这里存在多个函数，这里就不一一了解了，作用不大。

代码可见：D:\Github\Storage\c++\execlp

https://blog.csdn.net/weixin_39956356/article/details/86624472
不确定这句话真假：经常使用的是execve()。
注：只有execve是真正意义上的系统调用，其它都是在此基础上经过包装的库函数

## 5、从Linux程序中执行shell(程序、脚本)并获得输出结果
Unix界有一句名言：“一行shell脚本胜过万行C程序”，虽然这句话有些夸张，但不可否认的是，借助脚本确实能够极大的简化一些编程工作。比如实现一个ping程序来测试网络的连通性，实现ping函数需要写上200~300行代码，为什么不能直接调用系统的ping命令呢？通常在程序中通过 system函数来调用shell命令。但是，system函数仅返回命令是否执行成功，而我们可能需要获得shell命令在控制台上输出的结果。例如，执行外部命令ping后，如果执行失败，我们希望得到ping的返回信息。

### 5-1、使用临时文件
首先想到的方法就是将命令输出重定向到一个临时文件，在我们的应用程序中读取这个临时文件，获得外部命令执行结果，代码如下所示：



