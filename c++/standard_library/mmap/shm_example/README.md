参考：https://blog.csdn.net/ababab12345/article/details/102931841

writer.c 创建内存共享文件并写入数据。
reader.c 打开内存共享文件读数据。

如果写入程序调用了 shm_unlink("shm-file0001");则读者程序将无法打开共享内存文件。

注意：笔者认为，共享内存 与 内存映射是两个概念，并不是用shm_open 打开的文件一定要用mmap来映射才能在进程间共享，用常规的Linux函数write写入数据以后，仍然能够共享。

# 有一个点无法理解
int fd = shm_open("shm-file0001", O_CREAT|O_RDWR, 0777);
创建出来的文件权限对不上：
```
[root@ubuntu0006:/media/vdb/study] #stat /dev/shm/shm-file0001
  文件：'/dev/shm/shm-file0001'
  大小：1024            块：8          IO 块：4096   普通文件
设备：13h/19d   Inode：4           硬链接：1
权限：(0755/-rwxr-xr-x)  Uid：(    0/    root)   Gid：(    0/    root)
最近访问：2022-10-21 09:46:12.768000000 +0800
最近更改：2022-10-21 09:45:36.896000000 +0800
最近改动：2022-10-21 09:45:36.896000000 +0800
创建时间：-
```

# 以为只有
S_IRUSR：用户读权限
S_IWUSR：用户写权限
S_IRGRP：用户组读权限
S_IWGRP：用户组写权限
S_IROTH：其他组都权限
S_IWOTH：其他组写权限

https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-chmod-change-mode-file-directory
https://www.demo2s.com/c/c-sys-stat-h-usage-s-irwxg.html
通过上面的链接找到S_IRWXG|S_IRWXU|S_IRWXO这几个。



