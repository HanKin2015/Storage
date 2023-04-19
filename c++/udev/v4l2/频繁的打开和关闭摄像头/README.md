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
本地内核出现太多错误，需要测试本地系统是否正常打开摄像头，排查摄像头当前是什么状态，以及是什么原因导致，需要如何恢复异常。

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
代码见：D:\Github\Storage\c++\udev\v4l2\频繁的打开和关闭摄像头\epoll_pipe_demo.c

## 5、编写频繁切换分辨率的demo
参考：D:\Github\Storage\c++\udev\v4l2\验证VIDIOC_QBUF和VIDIOC_DQBUF\v4l2_tool.cpp
成果：D:\Github\Storage\c++\udev\v4l2\频繁的打开和关闭摄像头\v4l2_test_compatibility_tool.c

每次切换三个分辨率，160*120、320*240、160*120。
每次切换分辨率时，经历set probe设置分辨率和格式，然后打开摄像头，最后关闭摄像头。

交叉编译同一个文件可以运行在debian系统和安卓系统。

## 6、分析日志
更换性能更好的安卓客户端虽然也出现了问题，但是持续时间较长，近7个小时，之前那个只会在半个小时以内。
并且发现x86客户端已经跑了24个小时无问题，虽然摄像头也有所不同。

```
2023-04-14 15:47:11 [INFO] [3669:3670] libcam:0xf461d000 dev:/dev/video0, fd:6 {uvc_cli_do_probe:1208}
2023-04-14 15:47:11 [INFO] [3669:3670] [fmt]max:2 idx:0 {uvc_cli_do_probe:1209}
2023-04-14 15:47:11 [INFO] [3669:3670] [size]max:9 idx:2 {uvc_cli_do_probe:1210}
2023-04-14 15:47:11 [INFO] [3669:3670] setprop {libcam_setprop:1163}
2023-04-14 15:47:12 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:13 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:14 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:15 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:16 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:17 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:18 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:19 [INFO] [3669:3669] copy data to msg, len 52. {uvc_cli_send_event:950}
2023-04-14 15:47:21 [INFO] [3669:3670] set format failed[width:1280, heigth:720] errno:5(I/O error). {libcam_setprop:1175}
2023-04-14 15:47:21 [ERROR] [3669:3670] probe failed :-1 {uvc_cli_deal_event:767}
2023-04-14 15:47:21 [INFO] [3669:3670] uvc deal event:(7) failed. {uvc_cli_main_loop:855}
2023-04-14 15:47:21 [INFO] [3669:3670] num: 1 {uvc_cli_main_loop:831}
2023-04-14 15:47:21 [INFO] [3669:3670] get event:(1)UVC_CLI_START. {uvc_cli_deal_event:734}
2023-04-14 15:47:21 [INFO] [3669:3670] current work state:(1)CAMERA_READY {is_valid_event:675}
2023-04-14 15:47:21 [ERROR] [3669:3670] uvc's configure had not inited:0. {uvc_cli_deal_event:744}
2023-04-14 15:47:21 [INFO] [3669:3670] uvc deal event:(1) failed. {uvc_cli_main_loop:855}
2023-04-14 15:47:21 [INFO] [3669:3670] num: 1 {uvc_cli_main_loop:831}
```
出现问题时，会有大量的copy data to msg, len 52，开始以为是管道出现问题，没有进行接收数据导致，后面发现并非如此。
发现ioctl的超时为10秒，是由于在执行ioctl(ctx->fd, VIDIOC_S_FMT, &format)时卡住了，因为是单线程所以会导致管道收不到消息。
追踪到根源又发现在ioctl(cam_ctx->fd, VIDIOC_STREAMOFF, &type)关闭摄像头时会有5秒时间延长，设计的重复次数为10次，每次睡眠1秒。

不清楚是不是这个延长导致了后面设置分辨率失败的原因，尝试增加一个变量来告诉父进程我这边耽搁了5秒时间，在这5秒时间内不要向子线程发送消息。

## 7、基于6的修改出现了段错误
但是安卓无法进行gdb调试，看代码未看出任何异常，决定精简一下代码看是否能快速复现问题以及日志方便跟踪。
只有安卓+蓝色妖姬容易出现问题，其他情况暂未发现问题。
精简版(安卓独有版本)：D:\Github\Storage\c++\udev\v4l2\频繁的打开和关闭摄像头\v4l2_test_compatibility_tool_lite.c

修复安卓系统上assert函数不生效问题。
在安卓系统上，assert函数不会抛出异常。相反，它会在运行时检查一个条件是否为真，如果条件为假，则会导致程序崩溃并输出错误信息。这种行为被称为“断言失败”或“断言触发”。因此，在使用assert函数时，应该确保条件为真，否则程序将会崩溃。如果需要抛出异常来处理错误，可以使用其他异常处理机制，如try-catch语句。

使用abort函数抛出异常，报错Segmentation fault。在xubuntu中文版上面报错已放弃。
因此之前代码中出现Segmentation fault并不一定是段错误，可能是某个地方抛出异常了。





