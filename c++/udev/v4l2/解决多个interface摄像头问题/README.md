# 检查文件合法性
readelf命令
file命令
ldd命令

```
[admin@hankin ~]$ file check_usable_video
check_usable_video: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.32, BuildID[sha1]=7725f1125840591e2d849a5687c84c383348fca0, not stripped
[admin@hankin ~]$ file v4l2_tool
v4l2_tool: ELF 32-bit LSB shared object, ARM, version 1 (SYSV), dynamically linked (uses shared libs), BuildID[md5/uuid]=fc0c2e267d77e0d6b16e67d49daefe3e, stripped
[admin@hankin ~]$ file v4l2_tool_4.2
v4l2_tool_4.2: ELF 32-bit LSB shared object, ARM, version 1 (SYSV), dynamically linked (uses shared libs), stripped
```

## 多interface摄像头
```
root@hankin:~# ./a.out
===== GetBusidDevid(42) =====
open file /dev/video0 success.
UVCIOC_GET_BUSID_DEVICEID
open file /dev/video0 bus:1 dev:6.
open file /dev/video1 success.
UVCIOC_GET_BUSID_DEVICEID
video device(/dev/video1): get camera busid and deviceid failed.
open file /dev/video2 success.
UVCIOC_GET_BUSID_DEVICEID
open file /dev/video2 bus:1 dev:6.
open file /dev/video3 success.
UVCIOC_GET_BUSID_DEVICEID
video device(/dev/video3): get camera busid and deviceid failed.
===== GetNumberOfCameras(91) =====

*************************
opening /dev/video0:
Driver Info:                                driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x10101
                        capabilities: 0x84a00001.

*************************
opening /dev/video1:
Driver Info:                                driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x413c1
                        capabilities: 0x84a00001.

*************************
opening /dev/video2:
Driver Info:                                driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x10101
                        capabilities: 0x84a00001.

*************************
opening /dev/video3:
Driver Info:                                driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x413c1
                        capabilities: 0x84a00001.
there are 4 cameras.
===== GetPVidOfCameras(153) =====

opening /dev/video0:
char_card: 4c6f676974656368204252494f00000000000000000000000000000000000000, str: 4c6f676974656368204252494f00000000000000000000000000000000000000.

opening /dev/video1:
char_card: 4c6f676974656368204252494f00000000000000000000000000000000000000, str: 4c6f676974656368204252494f00000000000000000000000000000000000000.

opening /dev/video2:
char_card: 4c6f676974656368204252494f00000000000000000000000000000000000000, str: 4c6f676974656368204252494f00000000000000000000000000000000000000.

opening /dev/video3:
char_card: 4c6f676974656368204252494f00000000000000000000000000000000000000, str: 4c6f676974656368204252494f00000000000000000000000000000000000000.
===== GetInfoOfCameras(210) =====

*************************
opening /dev/video0:
Driver Info:
                              driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x10101
                        capabilities: 0x84a00001.
Support format:
        1.YUYV 4:2:2
        2.Motion-JPEG

*************************
opening /dev/video1:
Driver Info:
                              driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x413c1
                        capabilities: 0x84a00001.
Support format:

*************************
opening /dev/video2:
Driver Info:
                              driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x10101
                        capabilities: 0x84a00001.
Support format:
        1.8-bit Greyscale

*************************
opening /dev/video3:
Driver Info:
                              driver      : uvcvideo
                          card        : Logitech BRIO
                          bus_info    : usb-fd800000.usb-1.3.4
                          version     : 0x413c1
                        capabilities: 0x84a00001.
Support format:
root@hankin:~# ./check

****************/dev/video0****************
buf.length = 0, buf.bytesused = 0
buf.length = 614400, buf.bytesused = 614400
/dev/video0 can be open

****************/dev/video1****************
VIDIOC_G_FMT: Invalid argument
/dev/video1 can't be open

****************/dev/video2****************
select timeout
/dev/video2 can't be open

****************/dev/video3****************
VIDIOC_G_FMT: Invalid argument
/dev/video3 can't be open

****************/dev/video4****************
open camera path [ /dev/video4 ] failed.
```