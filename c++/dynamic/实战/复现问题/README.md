# 复现问题

## 1、未复现问题
单个so文件

## 2、难道是so嵌套so文件？
```
gcc -shared -o libmylib_caller.so mylib_caller.c -L. -lmylib_wrapper -fPIC

验证新的共享库: nm -D libmylib_caller.so
[root@ubuntu0006:~/cmake/debug] #nm -D libmylib_caller.so
0000000000200860 B __bss_start
0000000000000595 T call_hello
                 w __cxa_finalize
0000000000200860 D _edata
0000000000200868 B _end
00000000000005a8 T _fini
                 w __gmon_start__
                 U hello_wrapper
0000000000000490 T _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
[root@ubuntu0006:~/cmake/debug] #nm libmylib_caller.so
0000000000200860 B __bss_start
0000000000000595 T call_hello
0000000000200860 b completed.7243
                 w __cxa_finalize@@GLIBC_2.2.5
00000000000004e0 t deregister_tm_clones
0000000000000550 t __do_global_dtors_aux
0000000000200640 t __do_global_dtors_aux_fini_array_entry
0000000000200858 d __dso_handle
0000000000200648 d _DYNAMIC
0000000000200860 D _edata
0000000000200868 B _end
00000000000005a8 T _fini
0000000000000590 t frame_dummy
0000000000200638 t __frame_dummy_init_array_entry
0000000000000630 r __FRAME_END__
0000000000200838 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
00000000000005b4 r __GNU_EH_FRAME_HDR
                 U hello_wrapper
0000000000000490 T _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000000510 t register_tm_clones
0000000000200860 d __TMC_END__
```

编译：
gcc main.c -L. -lmylib_caller -Wl,-rpath=. ./libmylib.a -o main

果然复现问题了，欧耶！
```
root@32a43663383d ~
# gcc main.c -L. -lmylib_caller -Wl,-rpath=. ./libmylib.a -o main
/usr/bin/ld: warning: libmylib_wrapper.so, needed by ./libmylib_caller.so, not found (try using -rpath or -rpath-link)
/usr/bin/ld: ./libmylib_caller.so: undefined reference to `hello_wrapper'
collect2: error: ld returned 1 exit status
```

问题原因居然是libmylib_wrapper.so文件未找到导致的，发现只要删除这个文件就会出现这个问题：
```
[root@ubuntu0006:~/cmake/debug] #gcc main.c -L. -lmylib_caller -Wl,-rpath=. ./libmylib.a -o main_caller
/usr/bin/ld: warning: libmylib_wrapper.so, needed by ./libmylib_caller.so, not found (try using -rpath or -rpath-link)
./libmylib_caller.so：对‘hello_wrapper’未定义的引用
collect2: error: ld returned 1 exit status
```

之前排查思路就是错误的，后面发现将libmylib.a文件编译成so文件就可以解决这个问题，然而却忽略了/usr/bin/ld: warning: libmylib_wrapper.so, needed by ./libmylib_caller.so, not found (try using -rpath or -rpath-link)这句警告，因为发现这个警告存在的时候二进制文件也是能正常编译出来的。写完这个demo后才发现问题就是出现在这里。
