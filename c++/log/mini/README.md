## 测试结果
```
[root@ubuntu0006:~/mini] #gcc main.c
[root@ubuntu0006:~/mini] #./a.out
2024-01-16 16:06:02 [INFO] [4269:4269] [main.c:6:main] hello world
[root@ubuntu0006:~/mini] #ll /tmp/hankin.log
-rw-r--r-- 1 root root 534 1月  16 16:06 /tmp/hankin.log
[root@ubuntu0006:~/mini] #cat !$
cat /tmp/hankin.log
2024-01-16 16:03:59 [INFO] [783:783] [main.c:6:main] hello world
2024-01-16 16:05:57 [INFO] [4130:4130] [main.c:6:main] hello world
2024-01-16 16:05:58 [INFO] [4162:4162] [main.c:6:main] hello world
2024-01-16 16:06:00 [INFO] [4192:4192] [main.c:6:main] hello world
2024-01-16 16:06:01 [INFO] [4224:4224] [main.c:6:main] hello world
2024-01-16 16:06:01 [INFO] [4232:4232] [main.c:6:main] hello world
2024-01-16 16:06:02 [INFO] [4260:4260] [main.c:6:main] hello world
2024-01-16 16:06:02 [INFO] [4269:4269] [main.c:6:main] hello world
```