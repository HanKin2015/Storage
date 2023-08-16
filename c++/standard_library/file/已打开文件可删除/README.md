# 背景
已打开的文件，然后使用rm命令删除成功后，但是内存还是会一直在占用。
可以使用lsof命令可看见文件占用，或者使用进程号查看fd句柄。

# 已复现
代码见：D:\Github\Storage\c++\standard_library\file\已打开文件可删除\rm_but_used_memory.c

```
[root@ubuntu0006:~/cmake/rm] #df .
文件系统          1K-块     已用     可用 已用% 挂载点
/dev/vda1      80373576 56475864 19791936   75% /
[root@ubuntu0006:~/cmake/rm] #ll
总用量 58604
drwxr-xr-x 2 root root     4096 8月  16 11:42 ./
drwxr-xr-x 5 root root     4096 8月  16 11:42 ../
-rw-r--r-- 1 root root 60000000 8月  16 11:42 log.txt
[root@ubuntu0006:~/cmake/rm] #df .
文件系统          1K-块     已用     可用 已用% 挂载点
/dev/vda1      80373576 56534468 19733332   75% /
[root@ubuntu0006:~/cmake/rm] #du .
58600   .
[root@ubuntu0006:~/cmake/rm] #rm log.txt
[root@ubuntu0006:~/cmake/rm] #lsof | grep "log.txt"
lsof: WARNING: can't stat() fuse.gvfsd-fuse file system /run/user/108/gvfs
      Output information may be incomplete.
a.out     11365                   root    3u      REG              253,1  60000000    2622075 /root/cmake/rm/log.txt (deleted)
[root@ubuntu0006:~/cmake/rm] #du .
4       .
[root@ubuntu0006:~/cmake/rm] #df .
文件系统          1K-块     已用     可用 已用% 挂载点
/dev/vda1      80373576 56534468 19733332   75% /
```
可以发现，使用du命令是看不出来的，但是使用df则可以看出来内存还是在占用。