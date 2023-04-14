## 1、问题来源
```
[Mon Apr 10 19:44:14 2023] hankin-vcodec vpu_combo: closed
[Mon Apr 10 19:44:14 2023] uvcvideo: VIDIO_REQBUFS queue(ffffffc03386c510), count:2, dwMVFS: 153600, expect: 153600, saved: 0
[Mon Apr 10 19:44:16 2023] uvcvideo: VIDIO_REQBUFS queue(ffffffc03386c510), count:0, dwMVFS: 153600, expect: 153600, saved: 0
[Mon Apr 10 19:44:16 2023] hankin-vcodec vpu_combo: closed
[Mon Apr 10 19:44:16 2023] uvcvideo: VIDIO_REQBUFS queue(ffffffc03386c510), count:2, dwMVFS: 38400, expect: 38400, saved: 0
[Mon Apr 10 19:44:24 2023] uvcvideo: VIDIO_REQBUFS queue(ffffffc03386c510), count:0, dwMVFS: 38400, expect: 38400, saved: 0
[Mon Apr 10 19:44:24 2023] hankin-vcodec vpu_combo: closed
[Mon Apr 10 19:44:24 2023] uvcvideo: hankin->Failed to query (GET_CUR) UVC control 2816 on unit 256: -110 (exp. 2).
[Mon Apr 10 19:44:34 2023] uvcvideo: Failed to set UVC probe control : -110 (exp. 26).
[Mon Apr 10 19:44:44 2023] uvcvideo: Failed to set UVC probe control : -110 (exp. 26).
[Mon Apr 10 19:44:54 2023] uvcvideo: Failed to set UVC probe control : -110 (exp. 26).
[Mon Apr 10 19:44:55 2023] uvcvideo: hankin->Failed to query (GET_DEF) UVC control 5120 on unit 256: -110 (exp. 10).
[Mon Apr 10 19:44:55 2023] uvcvideo: hankin->Failed to query (SET_CUR) UVC control 5120 on unit 256: -110 (exp. 10).
[Mon Apr 10 19:44:55 2023] uvcvideo: hankin->Failed to query (GET_CUR) UVC control 512 on unit 512: -32 (exp. 2).
[Mon Apr 10 19:44:55 2023] dwc2 ff300000.usb: dwc2_update_urb_state(): trimming xfer length
[Mon Apr 10 19:44:55 2023] uvcvideo: hankin->Failed to query (GET_CUR) UVC control 2816 on unit 512: -75 (exp. 1).
[Mon Apr 10 19:44:55 2023] uvcvideo: hankin->Failed to query (GET_CUR) UVC control 2560 on unit 512: 1 (exp. 2).
[Mon Apr 10 19:44:55 2023] dwc2 ff300000.usb: dwc2_update_urb_state(): trimming xfer length
[Mon Apr 10 19:44:55 2023] uvcvideo: hankin->Failed to query (GET_CUR) UVC control 2816 on unit 512: -75 (exp. 1).
[Mon Apr 10 19:44:55 2023] uvcvideo: hankin->Failed to query (GET_CUR) UVC control 1024 on unit 256: 1 (exp. 4).
[Mon Apr 10 19:44:55 2023] dwc2 ff300000.usb: dwc2_update_urb_state(): trimming xfer length
```
本地内核出现太多错误，需要测试是否正常打开摄像头，排查摄像头当前是什么状态，以及是什么原因导致，需要如何恢复异常。

## 2、从代码和数据包来看应该是兼容性问题
目前测试在debian系统上面使用另外一款摄像头并没有什么问题。
但是蓝色妖姬在安卓系统上面不久就会出现I/O错误。
备注：有时候会连续出现6次左右的I/O错误，但是后面会恢复正常。。。。。。

## 3、技术栈
- 通过无名管道pipe进行通信
- 使用epoll多路复用

## 4、根据技术栈写通信demo
- 写两个文件client和server（使用pipe无法实现）
在C语言中，pipe函数只能在具有亲缘关系的父子进程之间进行通信，因为pipe函数是通过fork函数创建子进程后，子进程继承了父进程的文件描述符，从而实现了父子进程之间的通信。

如果要在两个非父子进程之间进行通信，可以使用其他的进程间通信方式，例如命名管道（named pipe）、消息队列（message queue）、共享内存（shared memory）等。这些进程间通信方式可以在不同的进程之间进行通信，而不需要亲缘关系。但是，这些进程间通信方式需要进行额外的设置和管理，因此使用起来相对复杂。

- 写成一个文件client_server
代码见：D:\Github\Storage\c++\udev\v4l2\判断摄像头设备是否可用\epoll_pipe_demo.c

## 5、编写频繁切换分辨率的demo
参考：D:\Github\Storage\c++\udev\v4l2\验证VIDIOC_QBUF和VIDIOC_DQBUF\v4l2_tool.cpp
成果：D:\Github\Storage\c++\udev\v4l2\判断摄像头设备是否可用\v4l2_test_compatibility_tool.c

每次切换三个分辨率，160*120、320*240、160*120。
每次切换分辨率时，经历set probe设置分辨率和格式，然后打开摄像头，最后关闭摄像头。

交叉编译同一个文件可以运行在debian系统和安卓系统。



