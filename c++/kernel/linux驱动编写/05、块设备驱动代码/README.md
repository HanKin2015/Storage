linux的设备驱动包括了char，block，net三种设备。char设备是比较简单的，只要分配了major、minor号，就可以进行读写处理了。相对而言，block和net要稍微复杂些。

为了将block和fs分开，kernel的设计者定义了request queue这一种形式。换一句话说，所有fs对block设备的请求，最终都会转变为request的形式。所以，对于block设备驱动开发的朋友来说，处理好了request queue就掌握了block设备的一半。当然，block设备很多，hd、floppy、ram都可以这么来定义。

## vmalloc和kmalloc
使用vmalloc分配非连续内存，适合大块内存分配，虚拟连续，物理不连续：分配的内存块在虚拟地址空间中是连续的，但物理地址可能不连续。
kmalloc物理连续：分配的内存块在物理地址上是连续的，因此虚拟地址也是连续的。

## 使用
a）make 一下，生成ramdisk.ko；
b）编译好了之后，就可以安装驱动了，在linux下是这么做的，sudo insmod ramdisk.ko；
c）安装好了，利用ls /dev/ramhd*， 就会发现在/dev下新增两个结点，即/dev/ramhda和/dev/ramhdb；
d）不妨选择其中一个节点进行分区处理， sudo fdisk /dev/ramhda，简单处理的话就建立一个分区， 生成/dev/ramhda1；
e）创建文件系统，sudo mkfs.ext3 /dev/ramhda1；
f）有了上面的文件系统，就可以进行mount处理，不妨sudo mount /dev/ramhda1 /mnt；
g）上面都弄好了，大家就可以copy、delete文件试试了，是不是很简单。



