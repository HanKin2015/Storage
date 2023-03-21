# ubuntu下使用wireshark软件

参考：https://cloud.tencent.com/developer/ask/sof/421861

## 1、安装
apt install wireshark
apt install tshark
dpkg-reconfigure wireshark-common或者弹出框勾选是即可

## 2、抓取键盘USB数据包
- 使用lsusb看见键盘挂载的总线编号为7
- 很重要需要加载usbmon驱动，否则wireshark无法抓包modprobe usbmon
- 执行wireshark选择usbmon7
- 按键abcdhj.保存abcd.pcapng文件
- 执行命令tshark -r abcd.pcapng -T fields -e usb.capdata > keypress_ids.txt
- 查看文件keypress_ids.txt符合预期

## 3、使用python脚本处理
代码见：
运行结果：
```
root@ubuntu160001:~# python3 deal_pcapng_file.py
Running the following bash command to convert the pcapng file to 00xx00000 nrs:
tshark -r 'abcd.pcapng' -T fields -e usb.capdata > keypress_ids.txt
Running as user "root" and group "root". This could be dangerous.
file=<_io.TextIOWrapper name='keypress_ids.txt' mode='r' encoding='UTF-8'>
line=00:00:04:00:00:00:00:00, relevant characters indicating keypress ID: 04 convert keypres ID to letter: a
two_chars: 00
line=00:00:05:00:00:00:00:00, relevant characters indicating keypress ID: 05 convert keypres ID to letter: b
two_chars: 00
line=00:00:06:00:00:00:00:00, relevant characters indicating keypress ID: 06 convert keypres ID to letter: c
two_chars: 00
line=00:00:07:00:00:00:00:00, relevant characters indicating keypress ID: 07 convert keypres ID to letter: d
two_chars: 00
line=00:00:0b:00:00:00:00:00, relevant characters indicating keypress ID: 0B convert keypres ID to letter: h
two_chars: 00
line=00:00:0d:00:00:00:00:00, relevant characters indicating keypress ID: 0D convert keypres ID to letter: j
two_chars: 00
line=00:00:37:00:00:00:00:00, relevant characters indicating keypress ID: 37 convert keypres ID to letter: .
two_chars: 00
```

## 4、使用pyshark库
在内网linux中安装pyshark失败，下载源码安装需要安装各种依赖，太多太多，失败告终。
使用外网运行看看：秒安装，并自动安装各种依赖。

