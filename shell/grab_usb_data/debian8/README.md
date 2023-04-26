## 20230311
测试发现开机启动只有limit_file_size.sh脚本执行了，grab_usb_data.sh脚本未执行。
但是直接执行limit_file_size.sh脚本后，grab_usb_data.sh脚本能执行。

暂时通过将grab_usb_data.sh脚本也写在开机脚本里面执行，测试发现开机启动都执行了。

## 开机自启动
开机自启动，将rv.local放在/etc/目录下面或者/etc/rc.d/目录下面