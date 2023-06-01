# 参考
https://blog.csdn.net/fjb2080/article/details/5009791
https://mirrors.edge.kernel.org/pub/linux/utils/kernel/hotplug/libudev/ch01.html

sudo apt-get install libudev1 libudev-dev

更多详情见：D:\Github\GitBook\gitbook\USBDevice\udev.md

还是无法正常编译，缺乏函数，可能是库太老了。
https://github.com/msekletar/udev/blob/master/libudev/libudev-monitor.c

```
/tmp/ccJKHkYj.o：在函数‘udevadm_monitor’中：
k.c:(.text+0x2bd)：对‘udev_monitor_new_from_socket’未定义的引用
collect2: error: ld returned 1 exit status
```

注意链接顺序，先前根据教程走，结果导致了很多错误：
```
/tmp/ccVEXz7x.o：在函数‘print_device’中：
k.c:(.text+0x65)：对‘udev_device_get_subsystem’未定义的引用
k.c:(.text+0x78)：对‘udev_device_get_devpath’未定义的引用
k.c:(.text+0x8c)：对‘udev_device_get_action’未定义的引用
k.c:(.text+0xd7)：对‘udev_device_get_properties_list_entry’未定义的引用
k.c:(.text+0xf0)：对‘udev_list_entry_get_value’未定义的引用
k.c:(.text+0x103)：对‘udev_list_entry_get_name’未定义的引用
k.c:(.text+0x127)：对‘udev_list_entry_get_next’未定义的引用
/tmp/ccVEXz7x.o：在函数‘udevadm_monitor’中：
k.c:(.text+0x2bd)：对‘udev_monitor_new_from_socket’未定义的引用
k.c:(.text+0x2f3)：对‘udev_monitor_enable_receiving’未定义的引用
k.c:(.text+0x33b)：对‘udev_monitor_new_from_netlink’未定义的引用
k.c:(.text+0x380)：对‘udev_monitor_enable_receiving’未定义的引用
k.c:(.text+0x3fc)：对‘udev_monitor_get_fd’未定义的引用
k.c:(.text+0x433)：对‘udev_monitor_get_fd’未定义的引用
k.c:(.text+0x47a)：对‘udev_monitor_get_fd’未定义的引用
k.c:(.text+0x4b1)：对‘udev_monitor_get_fd’未定义的引用
k.c:(.text+0x4ee)：对‘udev_monitor_get_fd’未定义的引用
/tmp/ccVEXz7x.o:k.c:(.text+0x504): 跟着更多未定义的参考到 udev_monitor_get_fd
/tmp/ccVEXz7x.o：在函数‘udevadm_monitor’中：
k.c:(.text+0x61a)：对‘udev_monitor_receive_device’未定义的引用
k.c:(.text+0x660)：对‘udev_device_unref’未定义的引用
k.c:(.text+0x682)：对‘udev_monitor_get_fd’未定义的引用
k.c:(.text+0x6ab)：对‘udev_monitor_get_fd’未定义的引用
k.c:(.text+0x6e7)：对‘udev_monitor_receive_device’未定义的引用
k.c:(.text+0x72a)：对‘udev_device_unref’未定义的引用
k.c:(.text+0x74c)：对‘udev_monitor_unref’未定义的引用
k.c:(.text+0x760)：对‘udev_monitor_unref’未定义的引用
/tmp/ccVEXz7x.o：在函数‘main’中：
k.c:(.text+0x7a4)：对‘udev_new’未定义的引用
k.c:(.text+0x7d1)：对‘udev_unref’未定义的引用
collect2: error: ld returned 1 exit status
```

就是编译链接的命令必须要写在最后，即
```
gcc -g -Wall -ludev udevadm.c -o myudevadm

gcc -g -Wall udevadm.c -o myudevadm -ludev
```

## 排查
在大多数 Linux 发行版中，libudev 库通常是作为 systemd 套件的一部分提供的。因此，你可以通过安装 systemd 套件来安装 libudev 库。

确认 libudev 库已经正确安装。你可以使用以下命令来查看 libudev 库的安装路径：
```
dpkg -L libudev-dev  # Debian/Ubuntu
rpm -ql libudev-devel  # Fedora/CentOS
```
如果 libudev 库的安装路径不在编译器的搜索路径中，你需要将其添加到搜索路径中。

将 libudev 库的路径添加到编译器的搜索路径中。你可以使用以下命令来指定 libudev 库的路径：
```
gcc -o myprogram myprogram.c -L/path/to/libudev -ludev
```
其中 /path/to/libudev 是 libudev 库的安装路径。

如果你使用的是 pkg-config 工具来编译程序，你可以使用以下命令来获取 libudev 库的编译选项：
```
pkg-config --libs libudev
```
然后将输出的编译选项添加到编译命令中即可。

如果你使用的是 CMake 工具来编译程序，你可以在 CMakeLists.txt 文件中添加以下代码来链接 libudev 库：
```
find_package(PkgConfig REQUIRED)
pkg_check_modules(UDEV REQUIRED libudev)
target_link_libraries(myprogram ${UDEV_LIBRARIES})
```
这样 CMake 就会自动查找并链接 libudev 库了。