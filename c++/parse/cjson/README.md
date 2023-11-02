# cJSON

## 1、纯c项目使用
gcc编译需要添加-lm参数，g++则不需要

## 2、是否存在内存泄露
果然发现了内存泄露问题。
```
gcc cJSON_example.c cJSON.c -lm -g -fsanitize=address
./a.out
valgrind --leak-check=full --show-reachable=yes --trace-children=yes ./a.out
```