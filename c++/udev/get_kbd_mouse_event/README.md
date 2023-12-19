## 1、/dev/input/mice和/dev/input/mouse0文件有什么区别
/dev/input/mice 和 /dev/input/mouse0 都是 Linux 系统中用于访问鼠标设备的特殊文件。

/dev/input/mice：这是一个设备文件，用于访问所有连接的鼠标设备。如果系统上有多个鼠标设备（例如多个物理鼠标或触摸板），可以使用 /dev/input/mice 来访问它们。读取该文件将允许读取所有鼠标设备的输入。

/dev/input/mouse0：这也是一个设备文件，用于访问特定的鼠标设备。如果系统上有多个鼠标设备，每个设备可能会有一个对应的 /dev/input/mouseX 文件，其中 X 是设备的编号。因此，/dev/input/mouse0 表示第一个鼠标设备的文件。

因此，区别在于 /dev/input/mice 可以用来访问所有鼠标设备的输入，而 /dev/input/mouse0 是特定鼠标设备的文件，用于访问该设备的输入。

但是我使用D:\Github\Storage\c++\udev\get_kbd_mouse_event\get_mouse_event2.c程序访问mice文件失败了。
另外我使用D:\Github\Storage\c++\udev\get_kbd_mouse_event\get_mouse_event.c程序在xubuntu上面正常，但是使用debian系统失败。
