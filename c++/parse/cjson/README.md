# cJSON

## 1、纯c项目使用
gcc编译需要添加-lm参数（报错cJSON.c:(.text+0x7bb)：对‘floor’未定义的引用），g++则不需要
需要引入cJSON.c和cJSON.h两个文件

## 2、是否存在内存泄露
果然发现了内存泄露问题。
```
gcc cJSON_example.c cJSON.c -lm -g -fsanitize=address
./a.out
valgrind --leak-check=full --show-reachable=yes --trace-children=yes ./a.out
```