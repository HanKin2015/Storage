# container_of函数

## 1、0指针的使用使用g++编译不通过
代码见：D:\Github\Storage\c++\container_of\0_pointer_useable.c

```
[root@ubuntu0006:~/cmake] #g++ 0_pointer_useable.cpp
0_pointer_useable.cpp: In function ‘int main()’:
0_pointer_useable.cpp:15:71: error: cast from ‘char*’ to ‘int’ loses precision [-fpermissive]
     printf("&((struct test *)0)->k = %d\n",((int)&((struct test *)0)->k));
                                                                       ^
[root@ubuntu0006:~/cmake] #mv 0_pointer_useable.cpp 0_pointer_useable.c
[root@ubuntu0006:~/cmake] #gcc 0_pointer_useable.c
0_pointer_useable.c: In function ‘main’:
0_pointer_useable.c:15:45: warning: cast from pointer to integer of different size [-Wpointer-to-int-cast]
     printf("&((struct test *)0)->k = %d\n",((int)&((struct test *)0)->k));
                                             ^
[root@ubuntu0006:~/cmake] #./a.out
&temp = 0x7ffd3dbf25f0
&temp.k = 0x7ffd3dbf25f8
&((struct test *)0)->k = 8
```

要解决这个问题，可以考虑使用 reinterpret_cast 进行类型转换，这样可以将指针类型转换为整数类型，而不会丢失精度。例如：
```
char* str = "hello";
int addr = reinterpret_cast<int>(str);
```






