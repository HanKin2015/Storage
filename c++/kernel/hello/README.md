可能需要内核头文件：
（01）找两台电脑，一台电脑安装windows系统，另外一台电脑安装linux系统，至于类型没有限制；
（02）查看linux系统的版本类型，输入uname -r即可；
（03）根据获取的linux kernel版本，在www.kernel.org上面寻找合适的kernel版本，直接用wget下载即可；
（04）用tar解压内核版本，将boot下config文件拷贝到本地，输入make menuconfig，直接保存即可；
（05）输入make -j2 & make modules_install & make install即可，系统重启；
（06）在linux系统起来后，注意在grub启动的时候选择刚刚编译的内核版本，这样就可以在linux上开发kernel驱动了；
（07）在windows 平台安装secureCRT工具，和linux取得连接；

涵盖编译安装卸载，查看安装日志，查看驱动状态。
```
[root@ubuntu0006:~/kernel/hj] #make
make -C /lib/modules/4.4.0-210-generic/build M=/root/kernel/hj modules
make[1]: Entering directory '/usr/src/linux-headers-4.4.0-210-generic'
  CC [M]  /root/kernel/hj/hello.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /root/kernel/hj/hello.mod.o
  LD [M]  /root/kernel/hj/hello.ko
make[1]: Leaving directory '/usr/src/linux-headers-4.4.0-210-generic'
[root@ubuntu0006:~/kernel/hj] #ll
总用量 108
drwxr-xr-x 3 root root  4096 7月   6 14:45 ./
drwxr-xr-x 4 root root  4096 7月   6 14:44 ../
-rw-r--r-- 1 root root   444 7月   6 14:44 hello.c
-rw-r--r-- 1 root root  4024 7月   6 14:45 hello.ko
-rw-r--r-- 1 root root   202 7月   6 14:45 .hello.ko.cmd
-rw-r--r-- 1 root root   767 7月   6 14:45 hello.mod.c
-rw-r--r-- 1 root root  2864 7月   6 14:45 hello.mod.o
-rw-r--r-- 1 root root 27866 7月   6 14:45 .hello.mod.o.cmd
-rw-r--r-- 1 root root  2032 7月   6 14:45 hello.o
-rw-r--r-- 1 root root 33499 7月   6 14:45 .hello.o.cmd
-rw-r--r-- 1 root root   243 7月   6 14:45 Makefile
-rw-r--r-- 1 root root    32 7月   6 14:45 modules.order
-rw-r--r-- 1 root root     0 7月   6 14:45 Module.symvers
drwxr-xr-x 2 root root  4096 7月   6 14:45 .tmp_versions/
[root@ubuntu0006:~/kernel/hj] #lsmod | grep hello
[root@ubuntu0006:~/kernel/hj] #insmod hello.ko
[root@ubuntu0006:~/kernel/hj] #dmesg -T | tail
[四 11月 16 17:01:16 2023] a.out[8173]: segfault at 7ffdc3d5f000 ip 0000000000400f03 sp 00007ffdc3d58a10 error 6 in a.out[400000+2000]
[四 11月 16 17:02:23 2023] a.out[9990]: segfault at 7ffcf52e2000 ip 0000000000400f25 sp 00007ffcf52dae50 error 6 in a.out[400000+2000]
[四 11月 16 19:42:06 2023] a.out[31052]: segfault at 0 ip 00007f177e37885d sp 00007fff7b4a5d90 error 4 in libc-2.23.so[7f177e30d000+1c0000]
[四 11月 16 22:15:54 2023] a.out[23618]: segfault at 38 ip 00007f5c93786d44 sp 00007ffdde414110 error 4 in libpthread-2.23.so[7f5c9377d000+18000]
[四 11月 16 22:17:14 2023] a.out[25993]: segfault at 38 ip 00007f89501d8d44 sp 00007ffd9f418830 error 4 in libpthread-2.23.so[7f89501cf000+18000]
[四 11月 16 22:18:00 2023] a.out[27203]: segfault at 38 ip 00007f7e64dd9d44 sp 00007ffd854ffa90 error 4 in libpthread-2.23.so[7f7e64dd0000+18000]
[一 11月 20 14:59:49 2023] ip_tables: (C) 2000-2006 Netfilter Core Team
[三 11月 22 15:31:19 2023] hello: loading out-of-tree module taints kernel.
[三 11月 22 15:31:19 2023] hello: module verification failed: signature and/or required key missing - tainting kernel
[三 11月 22 15:31:19 2023] hello, init
[root@ubuntu0006:~/kernel/hj] #lsmod | grep hello
hello                  16384  0
[root@ubuntu0006:~/kernel/hj] #rmmod hello
[root@ubuntu0006:~/kernel/hj] #lsmod | grep hello
[root@ubuntu0006:~/kernel/hj] #
```