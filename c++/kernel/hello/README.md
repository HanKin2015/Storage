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
[root@ubuntu0006:~/kernel/hj] #dmesg | tail
[23646740.929743] traps: a.out[15483] general protection ip:4007bb sp:7ffd1f5e1950 error:0 in a.out[400000+1000]
[23647957.982990] a.out[13858]: segfault at 0 ip 0000000000400fc6 sp 00007ffd1008d4e0 error 4 in a.out[400000+2000]
[23654824.240715] a.out[8308]: segfault at 0 ip 0000000000400fc2 sp 00007ffccc7b3240 error 4 in a.out[400000+2000]
[23655020.036725] a.out[1253]: segfault at 0 ip 000000000040113c sp 00007fff81864430 error 4 in a.out[400000+2000]
[23655106.012526] a.out[12564]: segfault at 0 ip 000000000040113c sp 00007fff5ddb5420 error 4 in a.out[400000+2000]
[23655319.293654] a.out[7798]: segfault at 0 ip 000000000040115a sp 00007ffffd315060 error 4 in a.out[400000+2000]
[23803277.169505] a.out[13077]: segfault at 40 ip 00007f191209834a sp 00007fff1962a830 error 4 in libusb-1.0.so.0.3.0[7f191208c000+1a000]
[23896430.538923] hello: loading out-of-tree module taints kernel.
[23896430.538963] hello: module verification failed: signature and/or required key missing - tainting kernel
[23896430.540080] hello, init
[root@ubuntu0006:~/kernel/hj] #lsmod | grep hello
hello                  16384  0
[root@ubuntu0006:~/kernel/hj] #rmmod hello
[root@ubuntu0006:~/kernel/hj] #lsmod | grep hello
[root@ubuntu0006:~/kernel/hj] #
```