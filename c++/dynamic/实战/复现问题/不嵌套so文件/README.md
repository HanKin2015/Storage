# 再次开启复现问题之路
之前的复现存在问题，并不是so文件缺失导致另外一个so文件中的函数未定义。

因为生成so文件时不需要函数定义，只需要导入头文件即可使用函数。在最终使用函数能找到函数定义即可。这个就是-fPIC存在的意义！
```
[root@ubuntu0006:~] #cat lib.h
void hello();
void hello()
{
}
[root@ubuntu0006:~] #cat main.c
#include <lib.h>

int main()
{
    hello();
    return 0;
}
[root@ubuntu0006:~] #gcc main.c lib.h
/tmp/ccNa0MqO.o：在函数‘main’中：
main.c:(.text+0xa)：对‘hello’未定义的引用
collect2: error: ld returned 1 exit status
[root@ubuntu0006:~] #gcc lib.h main.c
[root@ubuntu0006:~] #./a.out

# 删除hello函数定义
[root@ubuntu0006:~] #vi lib.h
[root@ubuntu0006:~] #gcc lib.h l.c
/tmp/ccxw2GW2.o：在函数‘main’中：
l.c:(.text+0xa)：对‘hello’未定义的引用
collect2: error: ld returned 1 exit status

# 生成so文件不需要hello函数定义
[root@ubuntu0006:~] #gcc -shared main.c -o main.so
/usr/bin/ld: /tmp/ccfZtp48.o: relocation R_X86_64_PC32 against undefined 符号 `hello' can not be used when making a shared object; recompile with -fPIC
/usr/bin/ld: 最后的链结失败: 错误的值
collect2: error: ld returned 1 exit status
[root@ubuntu0006:~] #gcc -fPIC -shared main.c -o main.so

# 删除hello();
[root@ubuntu0006:~] #vi main.c
[root@ubuntu0006:~] #gcc -shared main.c -o main.so
[root@ubuntu0006:~] #
```

前提：
session.c函数中不能出现turbo.h中函数直接调用，否则就能正常编译！

设计原则：
每个so模块独立编译，不要去依赖其他so或.a文件，最终在二进制集成的时候再把需要依赖的文件添加进去。

## 1、不嵌套
生成静态文件turbo.a：
gcc -c turbo.c -o turbo.o
ar rcs libturbo.a turbo.o

生成共享文件clnt.so：
gcc -fPIC -shared clnt.c -o libclnt.so

生成二进制文件session：
gcc session.c -lclnt libturbo.a -o session

## 2、嵌套创建文件
生成静态文件turbo.a：
gcc -c turbo.c -o turbo.o
ar rcs libturbo.a turbo.o

生成共享文件clnt.so：
gcc -fPIC -shared clnt.c -o libclnt.so

生成共享文件common.so:
gcc -fPIC -shared common.c -o libcommon.so

生成二进制文件session：
gcc d-session.c -lcommon -lclnt libturbo.a -o d-session

在一个环境gcc8中编译无问题，但是在另一个环境gcc10中报错：/usr/bin/ld: libturbo.a(turbo.o): relocation R_X86_64_32 against `.rodata' can not be used when making a PIE object; recompile with -fPIE
gcc -c turbo.c -fPIC -o turbo.o
ar rcs libturbo.a turbo.o

./a.out: error while loading shared libraries: libcommon.so: cannot open shared object file: No such file or directory
gcc d-session.c -L./ -lcommon -lclnt libturbo.a -Wl,-rpath,.

## 3、再嵌套创建文件
生成静态文件turbo.a：
gcc -c turbo.c -o turbo.o
ar rcs libturbo.a turbo.o

生成共享文件clnt.so：
gcc -fPIC -shared clnt.c -o libclnt.so

生成共享文件redir.so：
gcc -fPIC -shared redir.c -o libredir.so

生成共享文件common.so:
gcc -fPIC -shared common.c -o libcommon.so

生成二进制文件t-session：
gcc t-session.c -lcommon -lredir -lclnt libturbo.a -o t-session

## 2、注意静态文件链接的先后顺序
```
[root@ubuntu0006:~/hh] #gcc session.c libturbo.a -lclnt -lcommon -o session
./libcommon.so：对‘clnt’未定义的引用
collect2: error: ld returned 1 exit status
[root@ubuntu0006:~/hh] #gcc libturbo.a session.c -lclnt -lcommon -o session
/tmp/ccrrGxCL.o：在函数‘main’中：
session.c:(.text+0xa)：对‘hello’未定义的引用
./libcommon.so：对‘clnt’未定义的引用
./libclnt.so：对‘jpeg_set_defaults’未定义的引用
collect2: error: ld returned 1 exit status
```

技巧：一步一步的去添加依赖文件，也能了解文件之间的依赖性！
```
[root@ubuntu0006:~/hh] #gcc t-session.c
/tmp/ccVxVpX6.o：在函数‘main’中：
t-session.c:(.text+0xa)：对‘common_open’未定义的引用
collect2: error: ld returned 1 exit status
[root@ubuntu0006:~/hh] #gcc t-session.c -lcommon
./libcommon.so：对‘call_clnt’未定义的引用
collect2: error: ld returned 1 exit status
[root@ubuntu0006:~/hh] #gcc t-session.c -lcommon -lredir
./libredir.so：对‘clnt’未定义的引用
collect2: error: ld returned 1 exit status
[root@ubuntu0006:~/hh] #gcc t-session.c -lcommon -lredir -lclnt
./libclnt.so：对‘jpeg_set_defaults’未定义的引用
collect2: error: ld returned 1 exit status
[root@ubuntu0006:~/hh] #gcc t-session.c -lcommon -lredir -lclnt libturbo.a
[root@ubuntu0006:~/hh] #./a.out
numer = 12345
```



