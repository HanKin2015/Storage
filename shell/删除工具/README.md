# 1、rm命令添加-f参数后返回值都是0
```
[root@ubuntu0006:~] #rm p.pp
rm: 无法删除'p.pp': 没有那个文件或目录
[root@ubuntu0006:~] #echo $?
1
[root@ubuntu0006:~] #rm p.pp -f
[root@ubuntu0006:~] #echo $?
0
```