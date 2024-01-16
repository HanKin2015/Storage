# 日常小工具

## 1、背景
当有多个版本git仓库时，某个文件夹嵌套太多，来回切换不太方便。
每次在编译环境编译完成后，需要将二进制文件拷贝到运营环境中，长长的拷贝命令或者复杂的拖曳操作。

## 2、需求
快速进入指定文件夹
拷贝操作

## 3、制作安装包
make_package文件，执行linux_make_package.sh脚本即可。
```
[root@ubuntu0006:~/hh/make_package] #bash linux_make_package.sh
dos2unix: converting file install.sh to Unix format ...
updating: bin/ (stored 0%)
updating: bin/log.sh (deflated 36%)
updating: install.sh (deflated 34%)
dos2unix: converting file preinst.sh to Unix format ...
[root@ubuntu0006:~/hh/make_package] #./xxxx.bin l

EX: ./linux-xxx.bin install or uninstall

[root@ubuntu0006:~/hh/make_package] #./xxxx.bin install
Archive:  tmp.zip
   creating: /tmp/bin/
  inflating: /tmp/bin/log.sh
  inflating: /tmp/install.sh
[1]---------------package: unpack file success----------------
dos2unix: converting file ./bin/log.sh to Unix format ...
[2]------------package: install/uninstall file success----------------
[3]---------------package: clear resource success----------------

==================================================================
==================================================================
---------------- Please reboot your system ! ---------------------
==================================================================
==================================================================
[root@ubuntu0006:~/hh/make_package] #cat /tmp/make_package.log
2024-01-15 16:42:36.594 log.sh(20616): begin
2024-01-15 16:42:36.595 ./bin/log.sh(20616): main:58 hehehj
```