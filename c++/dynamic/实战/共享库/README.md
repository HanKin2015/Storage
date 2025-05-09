# 学习共享库

## 1、编译.so共享文件
```
创建共享库: gcc -shared -o libmylib_wrapper.so mylib_wrapper.c -L. -lmylib
/usr/bin/ld: ./libmylib.a(mylib.o): relocation R_X86_64_32 against `.rodata' can not be used when making a shared object; recompile with -fPIC
./libmylib.a: 无法添加符号: 错误的值
collect2: error: ld returned 1 exit status
解决方式：
编译源文件为目标文件: gcc -c mylib.c -o mylib.o -fPIC
创建静态库: ar rcs libmylib.a mylib.o
创建共享库: gcc -shared -o libmylib_wrapper.so mylib_wrapper.c -L. -lmylib -fPIC

验证共享库: nm -D libmylib_wrapper.so
[root@ubuntu0006:~/cmake/debug] #nm -D libmylib_wrapper.so
00000000002008e0 B __bss_start
                 w __cxa_finalize
00000000002008e0 D _edata
00000000002008e8 B _end
00000000000005fc T _fini
                 w __gmon_start__
00000000000005e6 T hello
00000000000005d5 T hello_wrapper
00000000000004b8 T _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U puts
```

## 2、使用共享库
```
gcc main.c -L. -lmylib_wrapper -o main
[root@ubuntu0006:~/cmake/debug] #./main
Hello, World!
```

## 3、创建共享库时可以不链接静态文件
```
[root@ubuntu0006:~/cmake/debug] #gcc -shared -o libmylib_wrapper.so mylib_wrapper.c -fPIC
[root@ubuntu0006:~/cmake/debug] #nm -D libmylib_wrapper.so
0000000000200840 B __bss_start
                 w __cxa_finalize
0000000000200840 D _edata
0000000000200848 B _end
0000000000000598 T _fini
                 w __gmon_start__
                 U hello
0000000000000585 T hello_wrapper
0000000000000478 T _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
```
会发现hello函数在此so文件中呈未定义状态。

但是在使用共享库的时候就会出现问题：
```
[root@ubuntu0006:~/cmake/debug] #gcc main.c -L. -lmylib_wrapper -o main
./libmylib_wrapper.so：对‘hello’未定义的引用
collect2: error: ld returned 1 exit status
```

解决方式：
```
gcc main.c -L. -lmylib_wrapper ./libmylib.a -o main
[root@ubuntu0006:~/cmake/debug] #./main
Hello, World!
```

## 4、迁移其他环境编译正常但是使用报错
```
# ./main 
./main: error while loading shared libraries: libmylib_wrapper.so: cannot open shared object file: No such file or directory

解决方式（在编译 main 可执行文件时，可以使用 -Wl,-rpath 选项来指定共享库的路径）：
gcc main.c -L. -lmylib_wrapper ./libmylib.a -Wl,-rpath=. -o main
```


